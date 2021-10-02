#include "VirtualMachine.h"

#include <iostream>

namespace Pomme
{
    VirtualMachine::VirtualMachine()
    : stackTop(stack.data())
    , frameCount(0)
    {
    }

	InterpretResult VirtualMachine::interpret(ObjFunction* function)
    {
        push(OBJ_VAL(function));

        CallFrame* frame = &frames[frameCount++];
        frame->function = function;
        frame->ip = function->chunk.code.data();
        frame->slots = stack.data();

        return run();
    }

    void VirtualMachine::defineGlobalNative(std::string name, NativeFn function)
    {
        //push(OBJ_VAL(copyString(name, (int)strlen(name))));
        //push(OBJ_VAL(newNative(function)));
        //tableSet(&vm.globals, AS_STRING(vm.stack[0]), vm.stack[1]);
        pop();
        pop();
    }

    void VirtualMachine::push(Value value)
    {
    	*stackTop = value;
        stackTop++;
    }

    Value VirtualMachine::pop()
    {
		stackTop--;
  		return *stackTop;
    }

	Value VirtualMachine::peek(int depth)
	{
		return stackTop[-1 - depth];
	}

    InterpretResult VirtualMachine::run()
    {
        CallFrame* frame = &frames[frameCount - 1];

        #define READ_BYTE() (*frame->ip++)
        #define READ_CONSTANT() (frame->function->chunk.constants[READ_BYTE()])
		#define READ_STRING() AS_STRING(READ_CONSTANT())
        #define READ_INT16() \
            (frame->ip += 2, (uint16_t)((frame->ip[-2] << 8) | frame->ip[-1]))

		#define BINARY_OP(valueType, op) \
			do { \
                double b = AS_NUMBER(pop()); \
                double a = AS_NUMBER(pop()); \
                push(valueType(a op b)); \
			} while (false)
        
        #define AS_OPCODE(code) static_cast<uint8_t>(code)

        for (;;)
        {
            uint8_t instruction;

            switch (instruction = READ_BYTE())
            {
                case AS_OPCODE(OpCode::OP_CONSTANT):
                {
                    Value constant = READ_CONSTANT();
					push(constant);
                    break;
                }

				case AS_OPCODE(OpCode::OP_NEGATE): 		push(NUMBER_VAL(-AS_NUMBER(pop()))); break;
				case AS_OPCODE(OpCode::OP_ADD):      	BINARY_OP(NUMBER_VAL, +); break;
				case AS_OPCODE(OpCode::OP_SUBTRACT): 	BINARY_OP(NUMBER_VAL, -); break;
				case AS_OPCODE(OpCode::OP_MULTIPLY): 	BINARY_OP(NUMBER_VAL, *); break;
				case AS_OPCODE(OpCode::OP_DIVIDE):   	BINARY_OP(NUMBER_VAL, /); break;

				case AS_OPCODE(OpCode::OP_POP):			pop(); break;

                case AS_OPCODE(OpCode::OP_PRINT):
                {
					printValue(pop());
                    printf("\n");
                    break;
                }

                case AS_OPCODE(OpCode::OP_GET_GLOBAL):
                {
                    uint16_t slot = READ_INT16();
                    push(globals[slot]);
                    break;
                }

                case AS_OPCODE(OpCode::OP_SET_GLOBAL):
                {
					uint16_t slot = READ_INT16();
                    globals[slot] = peek(0);
                    break;
                }

                case AS_OPCODE(OpCode::OP_GET_LOCAL):
                {
					uint8_t slot = READ_BYTE();
                    push(frame->slots[slot]);
                    break;
                }

                case AS_OPCODE(OpCode::OP_SET_LOCAL):
                {
					uint8_t slot = READ_BYTE();
                    frame->slots[slot] = peek(0);
                    break;
                }

                case AS_OPCODE(OpCode::OP_GET_PROPERTY):
                {
                    ObjInstance* instance = AS_INSTANCE(peek(0));
					uint16_t slot = READ_INT16();

                    pop(); // Instance.
                    push(instance->fields[slot]);

                    break;
                }

                case AS_OPCODE(OpCode::OP_SET_PROPERTY):
                {
					ObjInstance* instance = AS_INSTANCE(peek(1));
                    uint16_t slot = READ_INT16();
                    instance->fields[slot] = peek(0);

                    Value value = pop();
                    pop();
                    push(value);

                    break;
                }

                case AS_OPCODE(OpCode::OP_JUMP):
                {
					uint16_t offset = READ_INT16();
                    frame->ip += offset;
                    break;
                }

                case AS_OPCODE(OpCode::OP_JUMP_IF_FALSE):
                {
					uint16_t offset = READ_INT16();
                    if (isFalsey(peek(0))) frame->ip += offset;
                    break;
                }

                case AS_OPCODE(OpCode::OP_LOOP):
                {
					uint16_t offset = READ_INT16();
                    frame->ip -= offset;
                    break;
                }

                case AS_OPCODE(OpCode::OP_CALL):
                {
					int argCount = READ_BYTE();
                    if (!callValue(peek(argCount), argCount))
                    {
                        return InterpretResult::INTERPRET_RUNTIME_ERROR;
                    }

                    frame = &frames[frameCount - 1];
                    break;
                }

                case AS_OPCODE(OpCode::OP_RETURN):
                {
                    Value result = pop();
                    frameCount--;

                    if (frameCount == 0)
                    {
                        pop();
                        return InterpretResult::INTERPRET_OK;
                    }

                    stackTop = frame->slots;
                    push(result);

                    frame = &frames[frameCount - 1];
                    break;
                }

                case AS_OPCODE(OpCode::OP_INHERIT):
                {
                    Value superclass = peek(1);
                    ObjClass* subclass = AS_CLASS(peek(0));

                    //TODO: add all methods from superclass into subclass

                    pop(); // Subclass.
                    break;
                }

                case AS_OPCODE(OpCode::OP_METHOD):
                {
                    defineMethod(READ_INT16());
                    break;
                }

                case AS_OPCODE(OpCode::OP_GET_SUPER):
                {
                    ObjString* name = READ_STRING();
                    ObjClass* superclass = AS_CLASS(pop());
                    break;
                }

                case AS_OPCODE(OpCode::OP_NOT):
                {
                    push(BOOL_VAL(isFalsey(pop())));
                    break;
                }
            }
        }

        #undef READ_BYTE
        #undef READ_CONSTANT
		#undef READ_STRING
        #undef READ_SHORT
		#undef BINARY_OP
    }

    bool VirtualMachine::isFalsey(Value value)
    {
        return IS_NIL(value) || IS_NULL(value) || (IS_BOOL(value) && !AS_BOOL(value));
    }

    bool VirtualMachine::callValue(Value callee, int argCount)
    {
        if (IS_OBJ(callee))
        {
            switch (OBJ_TYPE(callee))
            {
                case ObjType::OBJ_BOUND_METHOD:
                {
                    ObjBoundMethod* bound = AS_BOUND_METHOD(callee);
                    stackTop[-argCount - 1] = bound->receiver;
                    return call(bound->method, argCount);
                }

                case ObjType::OBJ_CLASS:
                {
                    ObjClass* klass = AS_CLASS(callee);
                    stackTop[-argCount - 1] = OBJ_VAL(newInstance(klass));
                    if (klass->constructorIdx > -1)
                    {
                        return call(AS_FUNCTION(klass->methods[klass->constructorIdx]), argCount);
                    }
                    return true;
                }

                case ObjType::OBJ_FUNCTION: 
                    return call(AS_FUNCTION(callee), argCount);
                
                case ObjType::OBJ_NATIVE:
                {
                    std::function<Value(int, Value*)>& native = AS_NATIVE(callee);
                    Value result = native(argCount, stackTop - argCount);
                    
                    stackTop -= argCount + 1;
                    push(result);

                    return true;
                }

                default:
                    break; // Non-callable object type.
            }
        }

        return false;
    }

    bool VirtualMachine::call(ObjFunction* function, int argCount)
    {
        if (argCount != function->arity)
        {
            //runtimeError("Expected %d arguments but got %d.", function->arity, argCount);
            return false;
        }

        if (frameCount == FRAMES_MAX)
        {
            //runtimeError("Stack overflow.");
            return false;
        }

        CallFrame* frame = &frames[frameCount++];

        frame->function = function;
        frame->ip = function->chunk.code.data();
        frame->slots = stackTop - argCount - 1;

        return true;
    }

    void VirtualMachine::printValue(Value value)
    {
        switch (value.type)
        {
            case ValueType::VAL_BOOL:
                printf(AS_BOOL(value) ? "true" : "false");
                break;
            case ValueType::VAL_NIL: printf("nil"); break;
            case ValueType::VAL_NUMBER: printf("%g", AS_NUMBER(value)); break;
            case ValueType::VAL_OBJ: printObject(value); break;
        }
    }

    void VirtualMachine::printObject(Value value)
    {
        switch (OBJ_TYPE(value))
        {
            case ObjType::OBJ_BOUND_METHOD:
                printFunction(AS_BOUND_METHOD(value)->method);
                break;
            case ObjType::OBJ_CLASS:
                printf("%s", AS_CLASS(value)->name->chars.data());
                break;
            case ObjType::OBJ_FUNCTION:
                printFunction(AS_FUNCTION(value));
                break;
            case ObjType::OBJ_INSTANCE:
                printf("%s instance", AS_INSTANCE(value)->klass->name->chars.data());
                break;
            case ObjType::OBJ_NATIVE:
                printf("<native fn>");
                break;
            case ObjType::OBJ_STRING:
                printf("%s", AS_STDSTRING(value).data());
                break;
        }
    }

    void VirtualMachine::printFunction(ObjFunction* function)
    {
        printf("<fn %s>", function->name->chars.data());
    }

    void VirtualMachine::defineMethod(uint16_t slot)
    {
        Value method = peek(0);
        ObjClass* klass = AS_CLASS(peek(1));
        klass->methods[slot] = method;
        pop();
    }

    ObjInstance* VirtualMachine::newInstance(ObjClass* klass)
    {
        ObjInstance* instance = ALLOCATE_OBJ(ObjInstance, ObjType::OBJ_INSTANCE);
        instance->klass = klass;
        return instance;
    }

    ObjBoundMethod* VirtualMachine::newBoundMethod(Value receiver, ObjFunction* method)
    {
        ObjBoundMethod* bound = ALLOCATE_OBJ(ObjBoundMethod, ObjType::OBJ_BOUND_METHOD);
        bound->receiver = receiver;
        bound->method = method;
        return bound;
    }
}