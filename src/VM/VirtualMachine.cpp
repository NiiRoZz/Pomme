#include "VirtualMachine.h"
#include "CommonVisitorFunction.h"

#include <iostream>
#include <assert.h>

#define GC_HEAP_GROW_FACTOR 2

//#define USE_COMPUTED_GOTO

namespace Pomme
{
    VirtualMachine::VirtualMachine()
    : started(false)
    , frameCount(0u)
    , stackTop(stack)
    , globalsIndicesCount(0u)
    , objects(nullptr)
    , bytesAllocated(0u)
    , nextGC(1024u * 1024u)
    {
        grayStack.reserve(GLOBALS_MAX + STACK_MAX);
        for (uint8_t i = 0; i < static_cast<uint8_t>(PrimitiveType::COUNT); ++i)
        {
            primitives[i] = nullptr;
        }
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
        push(OBJ_VAL(static_cast<Obj*>(function)));
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

        assert(IS_FUNCTION(globals[it->second]));

        ObjFunction* function = AS_FUNCTION(globals[it->second]);

        if (function->arity != params.size())
        {
            return InterpretResult::INTERPRET_RUNTIME_ERROR; 
        }

        ObjFunction callFunction;
        callFunction.name = nullptr;
        callFunction.arity = 0u;
        callFunction.type = ObjType::OBJ_FUNCTION;

        callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_GET_GLOBAL), 0);
        callFunction.chunk.writeChunk(it->second, 0);

        for (int i = 0; i < params.size(); ++i)
        {
            int id = callFunction.chunk.addConstant(params[i]);
            callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_CONSTANT), 1);
            callFunction.chunk.writeChunk(id, 1);
        }

        callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_CALL_GLOBAL), 1);
        callFunction.chunk.writeChunk((params.size() >> 8) & 0xff, 1);
        callFunction.chunk.writeChunk(params.size() & 0xff, 1);

        callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_FINISH), 0);
        
        return interpret(&callFunction);
    }

    InterpretResult VirtualMachine::interpretMethodFunction(ObjInstance* instance, const std::string& methodName, const std::vector<Value>& params)
    {
        if (instance == nullptr) return InterpretResult::INTERPRET_RUNTIME_ERROR;

        auto it = instance->klass->methodsIndices.find(methodName);
        if (it == instance->klass->methodsIndices.end())
        {
            return InterpretResult::INTERPRET_RUNTIME_ERROR;
        }

        assert(IS_FUNCTION(instance->klass->methods[it->second]));

        ObjFunction* function = AS_FUNCTION(instance->klass->methods[it->second]);

        if (function->arity != params.size())
        {
            return InterpretResult::INTERPRET_RUNTIME_ERROR; 
        }

        ObjFunction callFunction;
        callFunction.name = nullptr;
        callFunction.arity = 0u;
        callFunction.type = ObjType::OBJ_FUNCTION;

        int id = callFunction.chunk.addConstant(OBJ_VAL(static_cast<Obj*>(instance)));
        callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_CONSTANT), 1);
        callFunction.chunk.writeChunk(id, 1);

        for (int i = 0; i < params.size(); ++i)
        {
            id = callFunction.chunk.addConstant(params[i]);
            callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_CONSTANT), 1);
            callFunction.chunk.writeChunk(id, 1);
        }

        callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_INVOKE), 1);
        callFunction.chunk.writeChunk((it->second >> 8) & 0xff, 1);
        callFunction.chunk.writeChunk(it->second & 0xff, 1);
        callFunction.chunk.writeChunk(0u, 1);
        callFunction.chunk.writeChunk((params.size() >> 8) & 0xff, 1);
        callFunction.chunk.writeChunk(params.size() & 0xff, 1);

        callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_FINISH), 0);
        
        return interpret(&callFunction);
    }

    std::optional<Value> VirtualMachine::callGlobalFunction(const std::string& name, const std::vector<Value>& params)
    {
        auto it = globalsIndices.find(name);
        if (it == globalsIndices.end())
        {
            return {};
        }

        assert(IS_FUNCTION(globals[it->second]));

        ObjFunction* function = AS_FUNCTION(globals[it->second]);

        if (function->arity != params.size())
        {
            return {};
        }

        push(globals[it->second]);

        for (int i = 0; i < params.size(); ++i)
        {
            push(params[i]);
        }

        ObjFunction callFunction;
        callFunction.name = function->name;
        callFunction.arity = function->arity;
        callFunction.type = ObjType::OBJ_FUNCTION;

        callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_CALL_GLOBAL), 1);
        callFunction.chunk.writeChunk((params.size() >> 8) & 0xff, 1);
        callFunction.chunk.writeChunk(params.size() & 0xff, 1);

        callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_FINISH), 1);

        if (!call(&callFunction, params.size()))
        {
            return {};
        }

        if (run() != InterpretResult::INTERPRET_OK)
        {
            return {};
        }

        return pop();
    }

    std::optional<Value> VirtualMachine::callMethodFunction(ObjInstance* instance, const std::string& methodName, const std::vector<Value>& params)
    {
        auto it = instance->klass->methodsIndices.find(methodName);
        if (it == instance->klass->methodsIndices.end())
        {
            return {};
        }

        assert(IS_FUNCTION(instance->klass->methods[it->second]));

        ObjFunction* function = AS_FUNCTION(instance->klass->methods[it->second]);

        if (function->arity != params.size())
        {
            return {};
        }

        push(OBJ_VAL(static_cast<Obj*>(instance)));

        for (int i = 0; i < params.size(); ++i)
        {
            push(params[i]);
        }

        ObjFunction callFunction;
        callFunction.name = function->name;
        callFunction.arity = function->arity;
        callFunction.type = ObjType::OBJ_FUNCTION;

        callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_INVOKE), 1);
        callFunction.chunk.writeChunk((it->second >> 8) & 0xff, 1);
        callFunction.chunk.writeChunk(it->second & 0xff, 1);
        callFunction.chunk.writeChunk(0u, 1);
        callFunction.chunk.writeChunk((params.size() >> 8) & 0xff, 1);
        callFunction.chunk.writeChunk(params.size() & 0xff, 1);

        callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_FINISH), 1);

        if (!call(&callFunction, params.size()))
        {
            return {};
        }

        if (run() != InterpretResult::INTERPRET_OK)
        {
            return {};
        }

        return pop();
    }

    bool VirtualMachine::linkGlobalNative(const std::string& name, GlobalNativeFn function)
    {
        auto it = globalsIndices.find(name);
        if (it == globalsIndices.end()) return false;

        assert(IS_GLOBAL_NATIVE(globals[it->second]));
 
        AS_GLOBAL_NATIVE(globals[it->second]) = function;

        return true;
    }

    bool VirtualMachine::linkMethodNative(const std::string& className, const std::string& methodName, MethodNativeFn function)
    {
        auto it = globalsIndices.find(className);
        if (it == globalsIndices.end()) return false;

        assert(IS_CLASS(globals[it->second]));

        ObjClass* klass = AS_CLASS(globals[it->second]);

        auto ot = klass->nativeMethodsIndices.find(methodName);
        if (ot == klass->nativeMethodsIndices.end()) return false;

        AS_METHOD_NATIVE(klass->nativeMethods[ot->second]) = function;

        return true;
    }

    bool VirtualMachine::linkMethodNative(const std::string& className, const std::string& methodName, MethodPrimitiveNativeFn function)
    {
        if (!CommonVisitorFunction::isNativeType(className)) return false;

        auto it = globalsIndices.find(className);
        if (it == globalsIndices.end()) return false;

        assert(IS_CLASS(globals[it->second]));

        ObjClass* klass = AS_CLASS(globals[it->second]);

        auto ot = klass->nativeMethodsIndices.find(methodName);
        if (ot == klass->nativeMethodsIndices.end()) return false;

        AS_METHOD_PRIMITIVE_NATIVE(klass->nativeMethods[ot->second]) = function;

        return true;
    }

    Value* VirtualMachine::getStaticField(const std::string& className, const std::string& fieldName)
    {
        auto it = globalsIndices.find(className);
        if (it == globalsIndices.end()) return nullptr;

        assert(IS_CLASS(globals[it->second]));

        ObjClass* klass = AS_CLASS(globals[it->second]);

        auto ot = klass->staticFieldsIndices.find(fieldName);
        if (ot == klass->staticFieldsIndices.end()) return nullptr;

        return &klass->staticFields[ot->second];
    }

    void VirtualMachine::push(const Value& value)
    {
    	*stackTop = value;
        stackTop++;

        #ifndef NDEBUG
        if ((stackTop - stack) >= STACK_MAX)
        {
            assert(false);
        }
        #endif
    }

    void VirtualMachine::push(Value&& value)
    {
    	*stackTop = std::move(value);
        stackTop++;

        #ifndef NDEBUG
        if ((stackTop - stack) >= STACK_MAX)
        {
            assert(false);
        }
        #endif
    }

    Value VirtualMachine::pop()
    {
		stackTop--;
  		return *stackTop;
    }

    void VirtualMachine::pop(int depth)
    {
		stackTop -= depth;
    }

	Value& VirtualMachine::peek(int depth)
	{
		return stackTop[-1 - depth];
	}

    ObjString* VirtualMachine::newString()
    {
        ObjString* string = allocateObject<ObjString>(ObjType::OBJ_STRING);
        return string;
    }

    ObjString* VirtualMachine::copyString(const char* chars, int length)
    {
        ObjString* string = newString();
        string->chars = std::move(std::string(chars, length));

        return string;
    }

    ObjInstance* VirtualMachine::newInstance(const std::string& className)
    {
        auto it = globalsIndices.find(className);
        if (it == globalsIndices.end()) return nullptr;

        return newInstance(AS_CLASS(globals[it->second]));
    }

    ObjFunction* VirtualMachine::newFunction()
    {
        ObjFunction* function = allocateObject<ObjFunction>(ObjType::OBJ_FUNCTION);
        function->arity = 0;
        function->name = NULL;
        return function;
    }

    ObjGlobalNative* VirtualMachine::newGlobalNative()
    {
        ObjGlobalNative* native = allocateObject<ObjGlobalNative>(ObjType::OBJ_GLOBAL_NATIVE);
        return native;
    }

    ObjMethodNative* VirtualMachine::newMethodNative()
    {
        ObjMethodNative* native = allocateObject<ObjMethodNative>(ObjType::OBJ_METHOD_NATIVE);
        return native;
    }

    ObjMethodPrimitiveNative* VirtualMachine::newMethodPrimitiveNative()
    {
        ObjMethodPrimitiveNative* native = allocateObject<ObjMethodPrimitiveNative>(ObjType::OBJ_METHOD_PRIMITIVE_NATIVE);
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
        std::cout << "          ";
        for (Value* slot = stack; slot < stackTop; ++slot)
        {
            std::cout << "[ ";
            printValue(*slot);
            std::cout << " ]";
        }
        std::cout << std::endl;
    }

    int VirtualMachine::stackSize()
    {
        return stackTop - stack;
    }

    InterpretResult VirtualMachine::run()
    {
        CallFrame* frame = &frames[frameCount - 1];

        #ifdef USE_COMPUTED_GOTO
        static void* dispatch_table[] = {
            &&OP_CONSTANT,
            &&OP_NULL,
            &&OP_TEST_NOT_NULL,
            &&OP_POP,
            &&OP_PRINT,
            &&OP_GET_GLOBAL,
            &&OP_SET_GLOBAL,
            &&OP_GET_LOCAL,
            &&OP_SET_LOCAL,
            &&OP_GET_PROPERTY,
            &&OP_SET_PROPERTY,
            &&OP_INVOKE,
            &&OP_JUMP,
            &&OP_JUMP_IF_FALSE,
            &&OP_LOOP,
            &&OP_CALL_NATIVE,
            &&OP_CALL_GLOBAL,
            &&OP_RETURN,
            &&OP_FINISH,
            &&OP_INHERIT,
            &&OP_METHOD,
            &&OP_FIELD,
            &&OP_INVOKE_SUPER,
            &&OP_NOT,
            &&OP_CLASS,
            &&OP_NEW,
            &&OP_INT,
            &&OP_FLOAT,
            &&OP_BOOL,
            &&OP_LT_INT_INT,
            &&OP_LT_INT_FLOAT,
            &&OP_LT_FLOAT_FLOAT,
            &&OP_LT_FLOAT_INT,
            &&OP_MINUS_INT_INT,
            &&OP_MINUS_INT_FLOAT,
            &&OP_MINUS_FLOAT_FLOAT,
            &&OP_MINUS_FLOAT_INT,
            &&OP_ADD_INT_INT,
            &&OP_ADD_INT_FLOAT,
            &&OP_ADD_FLOAT_FLOAT,
            &&OP_ADD_FLOAT_INT,
        };
        static_assert((sizeof(dispatch_table)/sizeof(dispatch_table[0])) == static_cast<uint8_t>(OpCode::COUNT));
        #endif

        #define READ_BYTE() (*frame->ip++)
        #define READ_CONSTANT() (frame->function->chunk.constants[READ_BYTE()])
		#define READ_STRING() AS_STRING(READ_CONSTANT())
        #define READ_UINT16() \
            (frame->ip += 2, (uint16_t)((frame->ip[-2] << 8) | frame->ip[-1]))
        #define READ_32BITS(type, name) \
            frame->ip += 4; type name; std::memcpy(&name, &(frame->ip[-4]), sizeof(type));
        #define READ_64BITS(type, name) \
            frame->ip += 8; type name; std::memcpy(&name, &(frame->ip[-8]), sizeof(type));
        
        #define AS_OPCODE(code) static_cast<uint8_t>(code)

        #ifdef USE_COMPUTED_GOTO
            #define DISPATCH() goto *dispatch_table[READ_BYTE()]
            #define CASES(name) name:
        #else
            #define DISPATCH() goto POMME_vm_main_loop
            #define CASES(name) case AS_OPCODE(OpCode::name):
        #endif

        #ifndef USE_COMPUTED_GOTO
        POMME_vm_main_loop:
        #else
        DISPATCH();
        #endif

        //printStack();
        //disassembleInstruction(&frame->function->chunk, (int)(frame->ip - frame->function->chunk.code.data()));
        
        #ifndef USE_COMPUTED_GOTO
        switch (READ_BYTE())
        {
        #endif

            CASES(OP_CONSTANT)
            {
                Value constant = READ_CONSTANT();
                push(constant);

                DISPATCH();
            }

            CASES(OP_NULL)
            {
                push(NULL_VAL);

                DISPATCH();
            } 

            CASES(OP_TEST_NOT_NULL)
            {
                bool isNull = IS_NULL(peek(0));
                Value value = BOOL_VAL(!isNull);

                pop(1u); //pop obj/null value
                push(value);

                DISPATCH();
            }

            CASES(OP_POP)
            {
                pop(1u);

                DISPATCH();
            }

            CASES(OP_PRINT)
            {
                printValue(pop());
                std::cout << "\n";

                DISPATCH();
            }

            CASES(OP_GET_GLOBAL)
            {
                push(globals[READ_BYTE()]);

                DISPATCH();
            }

            CASES(OP_SET_GLOBAL)
            {
                globals[READ_BYTE()] = peek(0);
                pop(1u);

                DISPATCH();
            }

            CASES(OP_GET_LOCAL)
            {
                push(frame->slots[READ_BYTE()]);

                DISPATCH();
            }

            CASES(OP_SET_LOCAL)
            {
                frame->slots[READ_BYTE()] = peek(0);
                pop(1u);

                DISPATCH();
            }

            CASES(OP_GET_PROPERTY)
            {
                assert(IS_INSTANCE(peek(0)) || IS_CLASS(peek(0)));

                uint16_t slot = READ_UINT16();

                Value* value = nullptr;

                if (IS_INSTANCE(peek(0)))
                {
                    ObjInstance* instance = AS_INSTANCE(peek(0));
                    value = &instance->fields[slot];
                }
                else
                {
                    ObjClass* klass = AS_CLASS(peek(0));
                    value = &klass->staticFields[slot];
                }

                pop(1u); // Instance or Class.
                push(*value);

                DISPATCH();
            }

            CASES(OP_SET_PROPERTY)
            {
                assert(IS_INSTANCE(peek(0)) || IS_CLASS(peek(0)));

                uint16_t slot = READ_UINT16();

                if (IS_INSTANCE(peek(0)))
                {
                    ObjInstance* instance = AS_INSTANCE(peek(0));
                    instance->fields[slot] = peek(1);
                }
                else
                {
                    ObjClass* klass = AS_CLASS(peek(0));
                    klass->staticFields[slot] = peek(1);
                }

                pop(2u); // Instance or Class. and Value

                DISPATCH();
            }

            CASES(OP_INVOKE)
            {
                uint16_t slot = READ_UINT16();
                bool native = READ_BYTE();
                uint16_t argCount = READ_UINT16();
                
                if (!invoke(argCount, slot, native))
                {
                    return InterpretResult::INTERPRET_RUNTIME_ERROR;
                }

                frame = &frames[frameCount - 1];

                DISPATCH();
            }

            CASES(OP_JUMP)
            {
                uint16_t offset = READ_UINT16();
                frame->ip += offset;

                DISPATCH();
            }

            CASES(OP_JUMP_IF_FALSE)
            {
                uint16_t offset = READ_UINT16();
                if (isFalsey(peek(0))) frame->ip += offset;

                DISPATCH();
            }

            CASES(OP_LOOP)
            {
                uint16_t offset = READ_UINT16();
                frame->ip -= offset;

                DISPATCH();
            }

            CASES(OP_CALL_NATIVE)
            {
                uint16_t argCount = READ_UINT16();
                if (!callNative(AS_GLOBAL_NATIVE(peek(argCount)), argCount))
                {
                    return InterpretResult::INTERPRET_RUNTIME_ERROR;
                }

                frame = &frames[frameCount - 1];

                DISPATCH();
            }

            CASES(OP_CALL_GLOBAL)
            {
                uint16_t argCount = READ_UINT16();
                if (!call(AS_FUNCTION(peek(argCount)), argCount))
                {
                    return InterpretResult::INTERPRET_RUNTIME_ERROR;
                }

                frame = &frames[frameCount - 1];

                DISPATCH();
            }

            CASES(OP_RETURN)
            {
                Value result = pop();
                frameCount--;

                if (frameCount == 0)
                {
                    pop(1u);
                    return InterpretResult::INTERPRET_OK;
                }

                stackTop = frame->slots;
                push(result);

                frame = &frames[frameCount - 1];

                DISPATCH();
            }

            CASES(OP_FINISH)
            {
                Value result = pop();
                frameCount--;

                pop(1u);

                if (frameCount > 0)
                {
                    push(result);
                }

                return InterpretResult::INTERPRET_OK; 
            }

            CASES(OP_INHERIT)
            {
                assert(IS_CLASS(peek(1)) && IS_CLASS(peek(0)));

                ObjClass* klass = AS_CLASS(peek(1));
                ObjClass* superclass = AS_CLASS(peek(0));

                std::memcpy(klass->nativeMethods, superclass->nativeMethods, sizeof(klass->nativeMethods));
                klass->nativeMethodsIndices = superclass->nativeMethodsIndices;

                std::memcpy(klass->methods, superclass->methods, sizeof(klass->methods));
                klass->methodsIndices = superclass->methodsIndices;

                pop(1u); // superclass.

                DISPATCH();
            }

            CASES(OP_METHOD)
            {
                uint16_t slot = READ_UINT16();
                ObjString* name = READ_STRING();
                bool native = READ_BYTE();

                defineMethod(slot, name, native);

                DISPATCH();
            }

            CASES(OP_FIELD)
            {
                uint16_t slot = READ_UINT16();
                ObjString* name = READ_STRING();
                bool isStatic = READ_BYTE();

                defineField(slot, name, isStatic);

                DISPATCH();
            }

            CASES(OP_INVOKE_SUPER)
            {
                uint16_t slot = READ_UINT16();
                bool native = READ_BYTE();
                assert(!native); //Temp
                uint16_t argCount = READ_UINT16();

                assert(IS_CLASS(peek(0)));
                ObjClass* superclass = AS_CLASS(pop());
                
                if (!call(AS_FUNCTION(superclass->methods[slot]), argCount))
                {
                    return InterpretResult::INTERPRET_RUNTIME_ERROR;
                }

                frame = &frames[frameCount - 1];

                DISPATCH();
            }

            CASES(OP_NOT)
            {
                assert(IS_BOOL(peek(0)));
                push(!AS_BOOL(peek(0)));

                DISPATCH();
            }

            CASES(OP_CLASS)
            {
                push(OBJ_VAL(static_cast<Obj*>(newClass(READ_STRING()))));

                DISPATCH();
            }

            CASES(OP_NEW)
            {
                uint16_t argCount = READ_UINT16();
                bool foundConstructor = READ_BYTE();
                uint16_t slot = READ_UINT16();

                assert(IS_CLASS(peek(argCount)));

                ObjClass* klass = AS_CLASS(peek(argCount));
                stackTop[-argCount - 1] = OBJ_VAL(static_cast<Obj*>(newInstance(klass)));

                if (foundConstructor)
                {
                    assert(slot >= 0u && slot < METHODS_MAX);
                    assert(IS_FUNCTION(klass->methods[slot]));

                    if (!call(AS_FUNCTION(klass->methods[slot]), argCount))
                    {
                        return InterpretResult::INTERPRET_RUNTIME_ERROR;
                    }

                    frame = &frames[frameCount - 1];
                }

                DISPATCH();
            }

            CASES(OP_INT)
            {
                READ_32BITS(uint32_t, value);
                push(INT_VAL(static_cast<int32_t>(value)));

                DISPATCH();
            }

            CASES(OP_FLOAT)
            {
                READ_64BITS(double, value);
                push(FLOAT_VAL(value));

                DISPATCH();
            }

            CASES(OP_BOOL)
            {
                push(BOOL_VAL(static_cast<bool>(READ_BYTE())));

                DISPATCH();
            }

            CASES(OP_LT_INT_INT)
            {
                Value value = BOOL_VAL(AS_INT(peek(1)) < AS_INT(peek(0)));

                pop(2u);

                push(std::move(value));

                DISPATCH();
            }

            CASES(OP_LT_INT_FLOAT)
            {
                Value value = BOOL_VAL((double) AS_INT(peek(1)) < AS_FLOAT(peek(0)));

                pop(2u);

                push(std::move(value));

                DISPATCH();
            }

            CASES(OP_LT_FLOAT_FLOAT)
            {
                Value value = BOOL_VAL(AS_FLOAT(peek(1)) < AS_FLOAT(peek(0)));

                pop(2u);

                push(std::move(value));

                DISPATCH();
            }

            CASES(OP_LT_FLOAT_INT)
            {
                Value value = BOOL_VAL(AS_FLOAT(peek(1)) < (double) AS_INT(peek(0)));

                pop(2u);

                push(std::move(value));

                DISPATCH();
            }

            CASES(OP_MINUS_INT_INT)
            {
                Value value = INT_VAL(AS_INT(peek(1)) - AS_INT(peek(0)));

                pop(2u);

                push(std::move(value));

                DISPATCH();
            }

            CASES(OP_MINUS_INT_FLOAT)
            {
                Value value = FLOAT_VAL((double) AS_INT(peek(1)) - AS_FLOAT(peek(0)));

                pop(2u);

                push(std::move(value));

                DISPATCH();
            }

            CASES(OP_MINUS_FLOAT_FLOAT)
            {
                Value value = FLOAT_VAL(AS_FLOAT(peek(1)) - AS_FLOAT(peek(0)));

                pop(2u);

                push(std::move(value));

                DISPATCH();
            }

            CASES(OP_MINUS_FLOAT_INT)
            {
                Value value = FLOAT_VAL(AS_FLOAT(peek(1)) - (double) AS_INT(peek(0)));

                pop(2u);

                push(std::move(value));

                DISPATCH();
            }

            CASES(OP_ADD_INT_INT)
            {
                Value value = INT_VAL(AS_INT(peek(1)) + AS_INT(peek(0)));

                pop(2u);

                push(std::move(value));

                DISPATCH();
            }

            CASES(OP_ADD_INT_FLOAT)
            {
                Value value = FLOAT_VAL((double) AS_INT(peek(1)) + AS_FLOAT(peek(0)));

                pop(2u);

                push(std::move(value));

                DISPATCH();
            }

            CASES(OP_ADD_FLOAT_FLOAT)
            {
                Value value = FLOAT_VAL(AS_FLOAT(peek(1)) + AS_FLOAT(peek(0)));

                pop(2u);

                push(std::move(value));

                DISPATCH();
            }

            CASES(OP_ADD_FLOAT_INT)
            {
                Value value = FLOAT_VAL(AS_FLOAT(peek(1)) + (double) AS_INT(peek(0)));

                pop(2u);

                push(std::move(value));

                DISPATCH();
            }
        #ifndef USE_COMPUTED_GOTO
        }
        #endif
        

        #undef READ_BYTE
        #undef READ_CONSTANT
		#undef READ_STRING
        #undef READ_SHORT
        #undef CASES
        #undef DISPATCH
    }

    void VirtualMachine::freeObject(Obj* object)
    {
        #ifdef DEBUG_LOG_GC
        std::cout << object << " free type " << ObjTypeToCStr(object->type) << std::endl;
        #endif

        switch (object->type)
        {
            case ObjType::OBJ_FUNCTION:
            {
                ObjFunction* function = static_cast<ObjFunction*>(object);
                bytesAllocated -= sizeof(ObjFunction);
                delete function;
                break;
            }

            case ObjType::OBJ_CLASS:
            {
                ObjClass* klass = static_cast<ObjClass*>(object);
                bytesAllocated -= sizeof(ObjClass);
                delete klass;
                break;
            } 

            case ObjType::OBJ_GLOBAL_NATIVE:
            {
                ObjGlobalNative* method = static_cast<ObjGlobalNative*>(object);
                bytesAllocated -= sizeof(ObjGlobalNative);
                delete method;
                break;
            }

            case ObjType::OBJ_METHOD_NATIVE:
            {
                ObjMethodNative* method = static_cast<ObjMethodNative*>(object);
                bytesAllocated -= sizeof(ObjMethodNative);
                delete method;
                break;
            }

            case ObjType::OBJ_METHOD_PRIMITIVE_NATIVE:
            {
                ObjMethodPrimitiveNative* method = static_cast<ObjMethodPrimitiveNative*>(object);
                bytesAllocated -= sizeof(ObjMethodPrimitiveNative);
                delete method;
                break;
            }

            case ObjType::OBJ_STRING:
            {
                ObjString* string = static_cast<ObjString*>(object);
                bytesAllocated -= sizeof(ObjString);
                delete string;
                break;
            }

            case ObjType::OBJ_INSTANCE:
            {
                ObjInstance* instance = static_cast<ObjInstance*>(object);
                bytesAllocated -= sizeof(ObjInstance);
                delete instance;
                break;
            }

            case ObjType::OBJ_BOUND_METHOD:
            {
                ObjBoundMethod* method = static_cast<ObjBoundMethod*>(object);
                bytesAllocated -= sizeof(ObjBoundMethod);
                delete method;
                break;
            }
        }
    }

    bool VirtualMachine::isFalsey(const Value& value)
    {
        if (IS_NULL(value)) return true;

        assert(IS_BOOL(value));

        return !AS_BOOL(value);
    }

    bool VirtualMachine::invoke(uint16_t argCount, uint16_t slot, bool native)
    {
        Value& parent = peek(argCount);

        ObjBoundMethod bound(parent, [&] () -> Value* {
            if (!IS_OBJ(parent))
                return (native) ? &primitives[static_cast<uint8_t>(getPrimitiveTypeFromValue(parent))]->nativeMethods[slot] : &primitives[static_cast<uint8_t>(getPrimitiveTypeFromValue(parent))]->methods[slot];

            if (IS_INSTANCE(parent))
            {
                ObjInstance* instance = AS_INSTANCE(parent);
                return (native) ? &instance->nativeMethods[slot] : &instance->klass->methods[slot];
            }

            assert(IS_CLASS(parent));
            ObjClass* klass = AS_CLASS(parent);
            return (native) ? &klass->nativeMethods[slot] : &klass->methods[slot];
        }());

        return callBoundMethod(bound, argCount);
    }

    bool VirtualMachine::callNative(GlobalNativeFn& nativeFn, uint16_t argCount)
    {
        Value result = nativeFn(*this, argCount, stackTop - argCount);
        
        stackTop -= argCount + 1;
        push(result);

        return true;
    }

    bool VirtualMachine::callBoundMethod(ObjBoundMethod& bound, uint16_t argCount)
    {
        if (IS_FUNCTION(*bound.method))
        {
            stackTop[-argCount - 1] = bound.receiver;
            return call(AS_FUNCTION(*bound.method), argCount);
        }

        Value result = [&] () {
            if (!IS_OBJ(bound.receiver))
            {
                MethodPrimitiveNativeFn& native = AS_METHOD_PRIMITIVE_NATIVE(*bound.method);
                assert(native);

                return native(*this, argCount, &bound.receiver, stackTop - argCount);
            }

            MethodNativeFn native = AS_METHOD_NATIVE(*bound.method);
            assert(native);
            return native(*this, argCount, AS_INSTANCE(bound.receiver), stackTop - argCount);
        }();

        stackTop -= argCount + 1;
        push(result);

        return true;
    }

    bool VirtualMachine::call(ObjFunction* function, uint16_t argCount)
    {
        #ifndef NDEBUG
        if (argCount != function->arity)
        {
            return false;
        }

        if (frameCount >= FRAMES_MAX)
        {
            assert(false);
        }
        #endif

        CallFrame* frame = &frames[frameCount++];

        frame->function = function;
        frame->ip = function->chunk.code.data();
        frame->slots = stackTop - argCount - 1;

        return true;
    }

    void VirtualMachine::printValue(const Value& value)
    {
        #ifdef NAN_BOXING

        if (IS_BOOL(value))
        {
            std::cout << AS_BOOL(value);
        }
        else if (IS_NULL(value))
        {
            std::cout << "null";
        }
        else if (IS_INT(value))
        {
            std::cout << AS_INT(value);
        }
        else if (IS_FLOAT(value))
        {
            std::cout << AS_FLOAT(value);
        }
        else if (IS_OBJ(value))
        {
            printObject(value);
        }

        #else

        if (value.isNull())
        {
            std::cout << "null";
            return;
        }

        if (value.isPrimitive())
        {
            const ObjPrimitive& primitive = value.asPrimitive();
            switch (primitive.type)
            {
                case PrimitiveType::INT:
                {
                    std::cout << primitive.as.number;
                    break;
                }

                
                case PrimitiveType::FLOAT:
                {
                    std::cout << primitive.as.numberFloat;
                    break;
                }

                
                case PrimitiveType::BOOL:
                {
                    std::cout << primitive.as.boolean;
                    break;
                }
            }
            return;
        }

        printObject(value);

        #endif
    }

    void VirtualMachine::printObject(const Value& value)
    {
        switch (OBJ_TYPE(value))
        {
            case ObjType::OBJ_BOUND_METHOD:
                printObject(*AS_BOUND_METHOD(value)->method);
                break;
            case ObjType::OBJ_CLASS:
                std::cout << "class " << AS_CLASS(value)->name->chars.c_str();
                break;
            case ObjType::OBJ_FUNCTION:
                printFunction(AS_FUNCTION(value));
                break;
            case ObjType::OBJ_INSTANCE:
                std::cout << AS_INSTANCE(value)->klass->name->chars.c_str() << " instance";
                break;
            case ObjType::OBJ_GLOBAL_NATIVE:
                std::cout << "<global native fn>";
                break;
            case ObjType::OBJ_METHOD_NATIVE:
                std::cout << "<method native fn>";
                break;
            case ObjType::OBJ_METHOD_PRIMITIVE_NATIVE:
                std::cout << "<method primitive native fn>";
                break;
            case ObjType::OBJ_STRING:
                std::cout << AS_CSTRING(value);
                break;
        }
    }

    void VirtualMachine::printFunction(ObjFunction* function)
    {
        if (function->name == nullptr)
        {
            std::cout << "<script>";
            return;
        }

        std::cout << "<fn " << function->name->chars << ">";
    }

    void VirtualMachine::defineMethod(uint16_t slot, ObjString* name, bool isNative)
    {
        std::cout << "VirtualMachine::defineMethod(" << slot << ", " << name->chars << ", " << isNative << ")" << std::endl;

        Value& method = peek(0);

        assert(IS_CLASS(peek(1)));

        ObjClass* klass = AS_CLASS(peek(1));

        if (isNative)
        {
            klass->nativeMethods[slot] = method;
            klass->nativeMethodsIndices.emplace(name->chars, slot);
        }
        else
        {
            klass->methods[slot] = method;
            klass->methodsIndices.emplace(name->chars, slot);
        }

        pop();
    }

    void VirtualMachine::defineField(uint16_t slot, ObjString* name, bool isStatic)
    {
        std::cout << "VirtualMachine::defineField(" << slot << ", " << name->chars << ", " << isStatic << ")" << std::endl;

        Value& value = peek(0);
        assert(IS_CLASS(peek(1)));

        ObjClass* klass = AS_CLASS(peek(1));

        if (isStatic)
        {
            klass->staticFields[slot] = value;
            klass->staticFieldsIndices.emplace(name->chars, slot);
        }
        else
        {
            klass->defaultFields[slot] = value;
            klass->fieldsIndices.emplace(name->chars, slot);
        }
        
        pop();
    }

    ObjClass* VirtualMachine::newClass(ObjString* name)
    {
        ObjClass* klass = allocateObject<ObjClass>(ObjType::OBJ_CLASS);
        klass->name = name;

        if (name->chars == "int")
        {
            primitives[static_cast<uint8_t>(PrimitiveType::INT)] = klass;
        }
        else if (name->chars == "float")
        {
            primitives[static_cast<uint8_t>(PrimitiveType::FLOAT)] = klass;
        }
        else if (name->chars == "bool")
        {
            primitives[static_cast<uint8_t>(PrimitiveType::BOOL)] = klass;
        }

        return klass;
    }

    ObjInstance* VirtualMachine::newInstance(ObjClass* klass)
    {
        ObjInstance* instance = allocateObject<ObjInstance>(ObjType::OBJ_INSTANCE);
        instance->klass = klass;
        std::memcpy(instance->fields, klass->defaultFields, sizeof(Value) * FIELDS_MAX);
        std::memcpy(instance->nativeMethods, klass->nativeMethods, sizeof(Value) * METHODS_MAX);
        return instance;
    }

    ObjBoundMethod* VirtualMachine::newBoundMethod(const Value& receiver, Value* method)
    {
        ObjBoundMethod* bound = allocateObject<ObjBoundMethod>(ObjType::OBJ_BOUND_METHOD);
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
            case AS_OPCODE(OpCode::OP_NULL):
                return simpleInstruction("OP_NULL", offset);
            case AS_OPCODE(OpCode::OP_TEST_NOT_NULL):
                return simpleInstruction("OP_TEST_NOT_NULL", offset);
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
            case AS_OPCODE(OpCode::OP_CALL_GLOBAL):
                return byteInstruction("OP_CALL_GLOBAL", chunk, offset);
            case AS_OPCODE(OpCode::OP_CALL_NATIVE):
                return byteInstruction("OP_CALL_NATIVE", chunk, offset);
            /*case AS_OPCODE(OpCode::OP_CLASS):
                return constantInstruction("OP_CLASS", chunk, offset);
            case AS_OPCODE(OpCode::OP_GET_PROPERTY):
                return constantInstruction("OP_GET_PROPERTY", chunk, offset);
            case AS_OPCODE(OpCode::OP_SET_PROPERTY):
                return constantInstruction("OP_SET_PROPERTY", chunk, offset);*/
            default:
                printf("Unknown opcode %d\n", instruction);
            return offset + 1;
        }
    }

    int VirtualMachine::simpleInstruction(const char* name, int offset)
    {
        std::cout << name << std::endl;
        return offset + 1;
    }

    int VirtualMachine::constantInstruction(const char* name, Chunk* chunk, int offset)
    {
        uint8_t constant = chunk->code[offset + 1];
        printf("%-16s %4d '", name, constant);
        printValue(chunk->constants[constant]);
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

    void VirtualMachine::collectGarbage()
    {
        #ifdef DEBUG_LOG_GC
        std::cout << "-- gc begin\n";
        std::size_t before = bytesAllocated;
        #endif

        markRoots();
        traceReferences();
        sweep();

        #ifndef DEBUG_STRESS_GC
        nextGC = bytesAllocated * GC_HEAP_GROW_FACTOR;
        #endif

        grayStack.clear();

        #ifdef DEBUG_LOG_GC
        std::cout << "-- gc end\n";
        std::cout << "   collected " << unsigned(before - bytesAllocated) << " bytes (from " << unsigned(before) << " to " << unsigned(bytesAllocated) << ") next at " << nextGC << std::endl;
        #endif
    }

    void VirtualMachine::markRoots()
    {
        for (Value* slot = stack; slot < stackTop; ++slot)
        {
            markValue(*slot);
        }

        for (std::size_t i = 0; i < frameCount; i++)
        {
            markObject(static_cast<Obj*>(frames[i].function));
        }

        for (std::size_t i = 0; i < globalsIndicesCount; i++)
        {
            markValue(globals[i]);
        }
    }

    void VirtualMachine::markValue(Value& value)
    {
        if (IS_OBJ(value)) markObject(AS_OBJ(value));
    }

    void VirtualMachine::markObject(Obj* object)
    {
        if (object == nullptr || object->isMarked) return;

        #ifdef DEBUG_LOG_GC
        std::cout << object << " mark ";
        printObject(object);
        std::cout << std::endl;
        #endif

        object->isMarked = true;

        grayStack.push_back(object);
    }

    void VirtualMachine::markArray(Value* array, std::size_t count)
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            markValue(array[i]);
        }
    }

    void VirtualMachine::traceReferences()
    {
        #ifdef DEBUG_LOG_GC
        std::cout << "grayStack.size() : " << grayStack.size() << std::endl;
        #endif

        for (std::size_t i = 0; i < grayStack.size(); ++i)
        {
            blackenObject(grayStack[i]);
        }
    }

    void VirtualMachine::blackenObject(Obj* object)
    {
        #ifdef DEBUG_LOG_GC
        std::cout << object << " blacken ";
        printObject(object);
        std::cout << std::endl;
        #endif

        switch (object->type)
        {
            case ObjType::OBJ_BOUND_METHOD:
            {
                ObjBoundMethod* bound = static_cast<ObjBoundMethod*>(object);
                markValue(bound->receiver);
                markValue(*bound->method);
                break;
            }

            case ObjType::OBJ_CLASS:
            {
                ObjClass* klass = static_cast<ObjClass*>(object);
                markObject(static_cast<Obj*>(klass->name));
                markArray(klass->methods, METHODS_MAX);
                markArray(klass->nativeMethods, METHODS_MAX);
                markArray(klass->staticFields, FIELDS_MAX);
                markArray(klass->defaultFields, FIELDS_MAX);
                break;
            }
            
            case ObjType::OBJ_FUNCTION:
            {
                ObjFunction* function = static_cast<ObjFunction*>(object);
                markObject(static_cast<Obj*>(function->name));
                markArray(function->chunk.constants.data(), function->chunk.constants.size());
                break;
            }

            case ObjType::OBJ_INSTANCE:
            {
                ObjInstance* instance = static_cast<ObjInstance*>(object);
                markObject(static_cast<Obj*>(instance->klass));
                markArray(instance->fields, FIELDS_MAX);
                markArray(instance->nativeMethods, METHODS_MAX);
                break;
            }

            case ObjType::OBJ_GLOBAL_NATIVE:
            case ObjType::OBJ_METHOD_NATIVE:
            case ObjType::OBJ_METHOD_PRIMITIVE_NATIVE:
            case ObjType::OBJ_STRING:
            break;
        }
    }

    void VirtualMachine::sweep()
    {
        Obj* previous = nullptr;
        Obj* object = objects;
        while (object != nullptr)
        {
            if (object->isMarked)
            {
                object->isMarked = false;
                previous = object;
                object = object->next;
            }
            else
            {
                Obj* unreached = object;
                object = object->next;

                if (previous != nullptr)
                {
                    previous->next = object;
                }
                else
                {
                    objects = object;
                }

                freeObject(unreached);
            }
        }
    }
}
