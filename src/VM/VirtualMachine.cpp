#include "VirtualMachine.h"
#include "Memory.h"

#include <iostream>
#include <assert.h>

namespace Pomme
{
    VirtualMachine::VirtualMachine()
    : stackTop(stack)
    , frameCount(0)
    , globalsIndicesCount(0)
    , objects(nullptr)
    {
    }

    VirtualMachine::~VirtualMachine()
    {
        Obj* object = objects;
        while (object != NULL)
        {
            Obj* next = object->next;
            freeObject(object);
            object = next;
        }
    }

	InterpretResult VirtualMachine::interpret(ObjFunction* function)
    {
        push(OBJ_VAL(function));
        call(function, 0);

        return run();
    }

    InterpretResult VirtualMachine::interpretGlobalFunction(const std::string& name, const std::vector<Value>& params)
    {
        auto it = globalsIndices.find(name);
        if (it == globalsIndices.end())
        {
            return InterpretResult::INTERPRET_RUNTIME_ERROR;
        }

        ObjFunction* function = AS_FUNCTION(globals[it->second]);

        assert(IS_FUNCTION(globals[it->second]));

        if (function->arity != params.size())
        {
            return InterpretResult::INTERPRET_RUNTIME_ERROR; 
        }

        ObjFunction* callFunction = newFunction();

        callFunction->chunk.writeChunk(AS_OPCODE(OpCode::OP_GET_GLOBAL), 0);
        callFunction->chunk.writeChunk(it->second, 0);

        for (int i = 0; i < params.size(); ++i)
        {
            int id = callFunction->chunk.addConstant(params[i]);
            callFunction->chunk.writeChunk(AS_OPCODE(OpCode::OP_CONSTANT), 1);
            callFunction->chunk.writeChunk(id, 1);
        }

        callFunction->chunk.writeChunk(AS_OPCODE(OpCode::OP_CALL), 1);
        callFunction->chunk.writeChunk(params.size(), 1);

        callFunction->chunk.writeChunk(AS_OPCODE(OpCode::OP_POP), 0);

        callFunction->chunk.writeChunk(AS_OPCODE(OpCode::OP_NULL), 0);
        callFunction->chunk.writeChunk(AS_OPCODE(OpCode::OP_RETURN), 0);
        
        return interpret(callFunction);
    }

    bool VirtualMachine::linkGlobalNative(const std::string& name, GlobalNativeFn function)
    {
        auto it = globalsIndices.find(name);
        if (it == globalsIndices.end()) return false;

        assert(IS_GLOBAL_NATIVE(globals[it->second]));
 
        AS_GLOBAL_NATIVE(globals[it->second]) = function;
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

    Obj* VirtualMachine::allocateObject(size_t size, ObjType type)
    {
        Obj* object = (Obj*)reallocate(NULL, 0, size);
        object->type = type;

        object->next = objects;
        objects = object;

        return object;
    }

    ObjString* VirtualMachine::allocateString(char* chars, int length)
    {
        ObjString* string = ALLOCATE_OBJ(this, ObjString, ObjType::OBJ_STRING);
        string->length = length;
        string->chars = chars;
        return string;
    }

    ObjString* VirtualMachine::copyString(const char* chars, int length)
    {
        char* heapChars = ALLOCATE(char, length + 1);
        std::memcpy(heapChars, chars, length);
        heapChars[length] = '\0';

        return allocateString(heapChars, length);
    }

    ObjFunction* VirtualMachine::newFunction()
    {
        ObjFunction* function = ALLOCATE_OBJ(this, ObjFunction, ObjType::OBJ_FUNCTION);
        function->arity = 0;
        function->name = NULL;
        initChunk(&function->chunk);
        return function;
    }

    ObjNative* VirtualMachine::newGlobalNative()
    {
        ObjNative* native = ALLOCATE_OBJ(this, ObjNative, ObjType::OBJ_GLOBAL_NATIVE);
        new (native) ObjNative();
        native->obj.type = ObjType::OBJ_GLOBAL_NATIVE;

        return native;
    }

    std::size_t VirtualMachine::addGlobal(const std::string& name)
    {
        std::size_t idx = globalsIndicesCount;
        globalsIndices.emplace(name, idx);
        globalsIndicesCount++;
        return idx;
    }

    std::optional<std::size_t> VirtualMachine::getGlobal(const std::string& name)
    {
        auto it = globalsIndices.find(name);
        if (it == globalsIndices.end())
        {
            return {};
        }

        return it->second;
    }

    void VirtualMachine::printStack()
    {
        printf("          ");
        for (Value* slot = stack; slot < stackTop; ++slot)
        {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
    }

    int VirtualMachine::stackSize()
    {
        return stackTop - stack;
    }

    InterpretResult VirtualMachine::run()
    {
        CallFrame* frame = &frames[frameCount - 1];

        #define READ_BYTE() (*frame->ip++)
        #define READ_CONSTANT() (frame->function->chunk.constants.values[READ_BYTE()])
		#define READ_STRING() AS_STRING(READ_CONSTANT())
        #define READ_UINT16() \
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
            //printStack();
            //disassembleInstruction(&frame->function->chunk, (int)(frame->ip - frame->function->chunk.code));

            uint8_t instruction;

            switch (instruction = READ_BYTE())
            {
                case AS_OPCODE(OpCode::OP_CONSTANT):
                {
                    Value constant = READ_CONSTANT();
					push(constant);
                    break;
                }

                case AS_OPCODE(OpCode::OP_NULL):        push(NULL_VAL); break;
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
                    uint8_t slot = READ_BYTE();
                    push(globals[slot]);
                    break;
                }

                case AS_OPCODE(OpCode::OP_SET_GLOBAL):
                {
					uint8_t slot = READ_BYTE();
                    globals[slot] = peek(0);
                    pop();
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
                    pop();
                    break;
                }

                case AS_OPCODE(OpCode::OP_GET_PROPERTY):
                {
                    ObjInstance* instance = AS_INSTANCE(peek(0));
					uint16_t slot = READ_UINT16();

                    pop(); // Instance.
                    push(instance->fields[slot]);

                    break;
                }

                case AS_OPCODE(OpCode::OP_SET_PROPERTY):
                {
					ObjInstance* instance = AS_INSTANCE(peek(0));
                    uint16_t slot = READ_UINT16();
                    instance->fields[slot] = peek(1);

                    pop(); // Instance.
                    break;
                }

                case AS_OPCODE(OpCode::OP_GET_METHOD):
                {
                    assert(IS_INSTANCE(peek(0)));
                    ObjInstance* instance = AS_INSTANCE(peek(0));
					uint16_t slot = READ_UINT16();

                    ObjBoundMethod* bound = newBoundMethod(peek(0), AS_FUNCTION(instance->klass->methods[slot]));
                    pop(); // Instance.
                    push(OBJ_VAL(bound));
                    break;
                }

                case AS_OPCODE(OpCode::OP_JUMP):
                {
					uint16_t offset = READ_UINT16();
                    frame->ip += offset;
                    break;
                }

                case AS_OPCODE(OpCode::OP_JUMP_IF_FALSE):
                {
					uint16_t offset = READ_UINT16();
                    if (isFalsey(peek(0))) frame->ip += offset;
                    break;
                }

                case AS_OPCODE(OpCode::OP_LOOP):
                {
					uint16_t offset = READ_UINT16();
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

                case AS_OPCODE(OpCode::OP_EQ):
                {
                    Value b = pop();
                    Value a = pop();
                    push(BOOL_VAL(valuesEqual(a, b)));
                    break;
                }

                case AS_OPCODE(OpCode::OP_LT):   	BINARY_OP(BOOL_VAL, <); break;

                case AS_OPCODE(OpCode::OP_INCR_POST):
                {
                    
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
                    uint16_t slot = READ_UINT16();
                    ObjString* name = READ_STRING();

                    defineMethod(slot, name);
                    break;
                }

                case AS_OPCODE(OpCode::OP_FIELD):
                {
                    uint16_t slot = READ_UINT16();
                    ObjString* name = READ_STRING();

                    defineField(slot, name);
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

                case AS_OPCODE(OpCode::OP_CLASS):
                {
                    push(OBJ_VAL(newClass(READ_STRING())));
                    break;
                }

                case AS_OPCODE(OpCode::OP_NEW):
                {
                    int argCount = READ_BYTE();
                    ObjClass* klass = AS_CLASS(peek(0));
                    stackTop[-argCount - 1] = OBJ_VAL(newInstance(klass));
                    /*if (klass->constructorIdx > -1)
                    {
                        return call(AS_FUNCTION(klass->methods[klass->constructorIdx]), argCount);
                    }
                    */
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

    void VirtualMachine::freeObject(Obj* object)
    {
        switch (object->type)
        {
            case ObjType::OBJ_FUNCTION:
            {
                ObjFunction* function = (ObjFunction*)object;
                freeChunk(&function->chunk);
                FREE(ObjFunction, object);
                break;
            }

            case ObjType::OBJ_CLASS:
            {
                FREE(ObjClass, object);
                break;
            } 

            case ObjType::OBJ_GLOBAL_NATIVE:
            {
                FREE(ObjNative, object);
                break;
            }

            case ObjType::OBJ_STRING:
            {
                ObjString* string = (ObjString*)object;
                FREE_ARRAY(char, string->chars, string->length + 1);
                FREE(ObjString, object);
                break;
            }

            case ObjType::OBJ_INSTANCE:
            {
                FREE(ObjInstance, object);
                break;
            }

            case ObjType::OBJ_BOUND_METHOD:
            {
                FREE(ObjBoundMethod, object);
                break;
            }
        }
    }

    bool VirtualMachine::isFalsey(Value value)
    {
        return IS_NIL(value) || IS_NULL(value) || (IS_BOOL(value) && !AS_BOOL(value));
    }

    bool VirtualMachine::valuesEqual(Value a, Value b)
    {
        if (a.type != b.type) return false;

        switch (a.type)
        {
            case ValueType::VAL_BOOL:   return AS_BOOL(a) == AS_BOOL(b);
            case ValueType::VAL_NIL:    return true;
            case ValueType::VAL_NUMBER: return AS_NUMBER(a) == AS_NUMBER(b);
            default:         return false; // Unreachable.
        }
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

                case ObjType::OBJ_FUNCTION: 
                    return call(AS_FUNCTION(callee), argCount);
                
                case ObjType::OBJ_GLOBAL_NATIVE:
                {
                    std::function<Value(int, Value*)>& native = AS_GLOBAL_NATIVE(callee);
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
        frame->ip = function->chunk.code;
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
            case ValueType::VAL_NULL: printf("null"); break;
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
                printf("class %s", AS_CLASS(value)->name->chars);
                break;
            case ObjType::OBJ_FUNCTION:
                printFunction(AS_FUNCTION(value));
                break;
            case ObjType::OBJ_INSTANCE:
                printf("%s instance", AS_INSTANCE(value)->klass->name->chars);
                break;
            case ObjType::OBJ_GLOBAL_NATIVE:
                printf("<native fn>");
                break;
            case ObjType::OBJ_STRING:
                printf("%s", AS_CSTRING(value));
                break;
        }
    }

    void VirtualMachine::printFunction(ObjFunction* function)
    {
        if (function->name == nullptr)
        {
            printf("<script>");
            return;
        }

        printf("<fn %s>", function->name->chars);
    }

    void VirtualMachine::defineMethod(uint16_t slot, ObjString* name)
    {
        std::cout << "VirtualMachine::defineMethod(" << slot << ", " << name->chars << ")" << std::endl;

        Value method = peek(0);

        assert(IS_CLASS(peek(1)));

        ObjClass* klass = AS_CLASS(peek(1));

        klass->methods[slot] = method;
        //klass->methodsIndices[name->chars] = slot;
        pop();
    }

    void VirtualMachine::defineField(uint16_t slot, ObjString* name)
    {
        std::cout << "VirtualMachine::defineField(" << slot << ", " << name->chars << ")" << std::endl;

        Value value = peek(0);

        assert(IS_CLASS(peek(1)));

        ObjClass* klass = AS_CLASS(peek(1));

        klass->fields_default[slot] = value;
        //klass->fieldsIndices[name->chars] = slot;
        pop();
    }

    ObjClass* VirtualMachine::newClass(ObjString* name)
    {
        ObjClass* klass = ALLOCATE_OBJ(this, ObjClass, ObjType::OBJ_CLASS);
        klass->name = name; 
        return klass;
    }

    ObjInstance* VirtualMachine::newInstance(ObjClass* klass)
    {
        ObjInstance* instance = ALLOCATE_OBJ(this, ObjInstance, ObjType::OBJ_INSTANCE);
        instance->klass = klass;
        std::memcpy(instance->fields, klass->fields_default, sizeof(Value) * FIELDS_MAX);
        return instance;
    }

    ObjBoundMethod* VirtualMachine::newBoundMethod(Value receiver, ObjFunction* method)
    {
        ObjBoundMethod* bound = ALLOCATE_OBJ(this, ObjBoundMethod, ObjType::OBJ_BOUND_METHOD);
        bound->receiver = receiver;
        bound->method = method;
        return bound;
    }

    int VirtualMachine::disassembleInstruction(Chunk* chunk, int offset)
    {
        printf("%04d ", offset);
        if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1])
        {
            printf("   | ");
        }
        else
        {
            printf("%4d ", chunk->lines[offset]);
        }

        uint8_t instruction = chunk->code[offset];
        switch (instruction)
        {
            case AS_OPCODE(OpCode::OP_CONSTANT):
                return constantInstruction("OP_CONSTANT", chunk, offset);
            case AS_OPCODE(OpCode::OP_RETURN):
                return simpleInstruction("OP_RETURN", offset);
            case AS_OPCODE(OpCode::OP_NOT):
                return simpleInstruction("OP_NOT", offset);
            case AS_OPCODE(OpCode::OP_NEGATE):
                return simpleInstruction("OP_NEGATE", offset);
            case AS_OPCODE(OpCode::OP_ADD):
                return simpleInstruction("OP_ADD", offset);
            case AS_OPCODE(OpCode::OP_SUBTRACT):
                return simpleInstruction("OP_SUBTRACT", offset);
            case AS_OPCODE(OpCode::OP_MULTIPLY):
                return simpleInstruction("OP_MULTIPLY", offset);
            case AS_OPCODE(OpCode::OP_DIVIDE):
                return simpleInstruction("OP_DIVIDE", offset);
            case AS_OPCODE(OpCode::OP_NULL):
                return simpleInstruction("OP_NULL", offset);
            case AS_OPCODE(OpCode::OP_TRUE):
                return simpleInstruction("OP_TRUE", offset);
            case AS_OPCODE(OpCode::OP_FALSE):
                return simpleInstruction("OP_FALSE", offset);
            case AS_OPCODE(OpCode::OP_EQ):
                return simpleInstruction("OP_EQ", offset);
            case AS_OPCODE(OpCode::OP_GT):
                return simpleInstruction("OP_GT", offset);
            case AS_OPCODE(OpCode::OP_LT):
                return simpleInstruction("OP_LT", offset);
            case AS_OPCODE(OpCode::OP_PRINT):
                return simpleInstruction("OP_PRINT", offset);
            case AS_OPCODE(OpCode::OP_POP):
                return simpleInstruction("OP_POP", offset);
            /*case AS_OPCODE(OpCode::OP_GET_GLOBAL):
                return constantInstruction("OP_GET_GLOBAL", chunk, offset);
            case AS_OPCODE(OpCode::OP_SET_GLOBAL):
                return constantInstruction("OP_SET_GLOBAL", chunk, offset);
            */
            case AS_OPCODE(OpCode::OP_GET_LOCAL):
                return byteInstruction("OP_GET_LOCAL", chunk, offset);
            case AS_OPCODE(OpCode::OP_SET_LOCAL):
                return byteInstruction("OP_SET_LOCAL", chunk, offset);
            case AS_OPCODE(OpCode::OP_JUMP):
                return jumpInstruction("OP_JUMP", 1, chunk, offset);
            case AS_OPCODE(OpCode::OP_JUMP_IF_FALSE):
                return jumpInstruction("OP_JUMP_IF_FALSE", 1, chunk, offset);
            case AS_OPCODE(OpCode::OP_LOOP):
                return jumpInstruction("OP_LOOP", -1, chunk, offset);
            case AS_OPCODE(OpCode::OP_CALL):
                return byteInstruction("OP_CALL", chunk, offset);
            case AS_OPCODE(OpCode::OP_CLASS):
                return constantInstruction("OP_CLASS", chunk, offset);
            /*case AS_OPCODE(OpCode::OP_GET_PROPERTY):
                return constantInstruction("OP_GET_PROPERTY", chunk, offset);
            case AS_OPCODE(OpCode::OP_SET_PROPERTY):
                return constantInstruction("OP_SET_PROPERTY", chunk, offset);
            case AS_OPCODE(OpCode::OP_GET_METHOD):
                return constantInstruction("OP_GET_METHOD", chunk, offset);*/
            default:
                printf("Unknown opcode %d\n", instruction);
            return offset + 1;
        }
    }

    int VirtualMachine::simpleInstruction(const char* name, int offset)
    {
        printf("%s\n", name);
        return offset + 1;
    }

    int VirtualMachine::constantInstruction(const char* name, Chunk* chunk, int offset)
    {
        uint8_t constant = chunk->code[offset + 1];
        printf("%-16s %4d '", name, constant);
        printValue(chunk->constants.values[constant]);
        printf("'\n");
        return offset + 2;
    }

    int VirtualMachine::byteInstruction(const char* name, Chunk* chunk, int offset)
    {
        uint8_t slot = chunk->code[offset + 1];
        printf("%-16s %4d\n", name, slot);
        return offset + 2;
    }

    int VirtualMachine::jumpInstruction(const char* name, int sign, Chunk* chunk, int offset)
    {
        uint16_t jump = (uint16_t)(chunk->code[offset + 1] << 8);
        jump |= chunk->code[offset + 2];
        printf("%-16s %4d -> %d\n", name, offset, offset + 3 + sign * jump);
        return offset + 3;
    }
}