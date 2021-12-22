#include "VirtualMachine.h"
#include "CommonVisitorFunction.h"

#include <iostream>
#include <assert.h>

#define GC_HEAP_GROW_FACTOR 2

//#define USE_COMPUTED_GOTO

namespace Pomme
{
    VirtualMachine::VirtualMachine()
    : frameCount(0u)
    , stackTop(stack)
    , globalsIndicesCount(0u)
    //, objects(nullptr)
    //, bytesAllocated(0u)
    //, nextGC(1024u * 1024u)
    , objectMemory(1000000u * 10u)
    {
        std::memset(globals, 0, sizeof(Value) * GLOBALS_MAX);
        //grayStack.reserve(GLOBALS_MAX + STACK_MAX);
        for (uint8_t i = 0; i < static_cast<uint8_t>(PrimitiveType::COUNT); ++i)
        {
            primitives[i] = nullptr;
        }
    }

    VirtualMachine::~VirtualMachine()
    {
    }

	InterpretResult VirtualMachine::interpret(ObjFunction* function)
    {
        push(OBJ_PTR_VAL(function->pointer));
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

        assert(IS_FUNCTION(*this, globals[it->second]));

        ObjFunction* function = AS_FUNCTION(*this, globals[it->second]);

        if (function->arity != params.size())
        {
            return InterpretResult::INTERPRET_RUNTIME_ERROR; 
        }

        ObjFunction& callFunction = *(allocateObject<ObjFunction>());
        callFunction.name = nullptr;
        callFunction.arity = 0u;
        callFunction.type = ObjType::OBJ_FUNCTION;

        callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_GET_GLOBAL), 0);
        callFunction.chunk.writeChunk(it->second, 0);

        for (std::size_t i = 0; i < params.size(); ++i)
        {
            int id = callFunction.chunk.addConstant(params[i]);
            callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_CONSTANT), 1);
            callFunction.chunk.writeChunk(id, 1);
        }

        callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_CALL_GLOBAL), 1);
        callFunction.chunk.writeChunk((params.size() >> 8) & 0xff, 1);
        callFunction.chunk.writeChunk(params.size() & 0xff, 1);

        callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_RETURN), 2);
        
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

        assert(IS_FUNCTION(*this, *(instance->klass->getMethod(*this, it->second))));

        ObjFunction* function = AS_FUNCTION(*this, *(instance->klass->getMethod(*this, it->second)));

        if (function->arity != params.size())
        {
            return InterpretResult::INTERPRET_RUNTIME_ERROR; 
        }

        ObjFunction& callFunction = *(allocateObject<ObjFunction>());
        callFunction.name = nullptr;
        callFunction.arity = 0u;
        callFunction.type = ObjType::OBJ_FUNCTION;

        int id = callFunction.chunk.addConstant(OBJ_PTR_VAL(instance->pointer));
        callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_CONSTANT), 1);
        callFunction.chunk.writeChunk(id, 1);

        for (std::size_t i = 0; i < params.size(); ++i)
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

        callFunction.chunk.writeChunk(AS_OPCODE(OpCode::OP_RETURN), 2);
        
        return interpret(&callFunction);
    }

    std::optional<Value> VirtualMachine::callGlobalFunction(const std::string& name, const std::vector<Value>& params)
    {
        auto it = globalsIndices.find(name);
        if (it == globalsIndices.end())
        {
            return {};
        }

        assert(IS_FUNCTION(*this, globals[it->second]));

        //TODO: call native global function

        ObjFunction* function = AS_FUNCTION(*this, globals[it->second]);

        if (function->arity != params.size())
        {
            return {};
        }

        push(globals[it->second]);

        for (std::size_t i = 0; i < params.size(); ++i)
        {
            push(params[i]);
        }

        if (!call(function, params.size()))
        {
            return {};
        }

        if (run(true) != InterpretResult::INTERPRET_OK)
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
            auto ot = instance->klass->nativeMethodsIndices.find(methodName);
            if (ot == instance->klass->nativeMethodsIndices.end())
            {
                return {};
            }

            //TODO: call native method
            return {};
        }

        assert(IS_FUNCTION(*this, *(instance->klass->getMethod(*this, it->second))));

        ObjFunction* function = AS_FUNCTION(*this, *(instance->klass->getMethod(*this, it->second)));

        if (function->arity != params.size())
        {
            return {};
        }

        push(OBJ_PTR_VAL(instance->pointer));

        for (std::size_t i = 0; i < params.size(); ++i)
        {
            push(params[i]);
        }

        if (!call(function, params.size()))
        {
            return {};
        }

        if (run(true) != InterpretResult::INTERPRET_OK)
        {
            return {};
        }

        return pop();
    }

    bool VirtualMachine::linkGlobalNative(const std::string& name, GlobalNativeFn function)
    {
        auto it = globalsIndices.find(name);
        if (it == globalsIndices.end()) return false;

        assert(IS_GLOBAL_NATIVE(*this, globals[it->second]));
 
        AS_GLOBAL_NATIVE(*this, globals[it->second]) = function;

        return true;
    }

    bool VirtualMachine::linkMethodNative(const std::string& className, const std::string& methodName, MethodNativeFn function)
    {
        auto it = globalsIndices.find(className);
        if (it == globalsIndices.end()) return false;

        assert(IS_CLASS(*this, globals[it->second]));

        ObjClass* klass = AS_CLASS(*this, globals[it->second]);

        auto ot = klass->nativeMethodsIndices.find(methodName);
        if (ot == klass->nativeMethodsIndices.end()) return false;

        AS_METHOD_NATIVE(*this, *(klass->getNativeMethod(*this, ot->second))) = function;

        return true;
    }

    bool VirtualMachine::linkMethodNative(const std::string& className, const std::string& methodName, MethodPrimitiveNativeFn function)
    {
        if (!CommonVisitorFunction::isNativeType(className)) return false;

        auto it = globalsIndices.find(className);
        if (it == globalsIndices.end()) return false;

        assert(IS_CLASS(*this, globals[it->second]));

        ObjClass* klass = AS_CLASS(*this, globals[it->second]);

        auto ot = klass->nativeMethodsIndices.find(methodName);
        if (ot == klass->nativeMethodsIndices.end()) return false;

        AS_METHOD_PRIMITIVE_NATIVE(*this, *(klass->getNativeMethod(*this, ot->second))) = function;

        return true;
    }

    Value* VirtualMachine::getStaticField(const std::string& className, const std::string& fieldName) const
    {
        auto it = globalsIndices.find(className);
        if (it == globalsIndices.end()) return nullptr;

        assert(IS_CLASS(*this, globals[it->second]));

        ObjClass* klass = AS_CLASS(*this, globals[it->second]);

        auto ot = klass->staticFieldsIndices.find(fieldName);
        if (ot == klass->staticFieldsIndices.end()) return nullptr;

        return klass->getStaticField(*this, ot->second);
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

	Value& VirtualMachine::peek(int depth) const
	{
		return stackTop[-1 - depth];
	}

    ObjString* VirtualMachine::newString()
    {
        ObjString* string = allocateObject<ObjString>();
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

        return newInstance(AS_CLASS(*this, globals[it->second]));
    }

    ObjFunction* VirtualMachine::newFunction()
    {
        ObjFunction* function = allocateObject<ObjFunction>();
        function->arity = 0;
        function->name = NULL;
        return function;
    }

    ObjGlobalNative* VirtualMachine::newGlobalNative()
    {
        ObjGlobalNative* native = allocateObject<ObjGlobalNative>();
        return native;
    }

    ObjMethodNative* VirtualMachine::newMethodNative()
    {
        ObjMethodNative* native = allocateObject<ObjMethodNative>();
        return native;
    }

    ObjMethodPrimitiveNative* VirtualMachine::newMethodPrimitiveNative()
    {
        ObjMethodPrimitiveNative* native = allocateObject<ObjMethodPrimitiveNative>();
        return native;
    }

    std::size_t VirtualMachine::addGlobal(const std::string& name)
    {
        std::size_t idx = globalsIndicesCount;
        globalsIndices.emplace(name, idx);
        globalsIndicesCount++;
        return idx;
    }

    std::optional<std::size_t> VirtualMachine::getGlobal(const std::string& name) const
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

    int VirtualMachine::stackSize() const
    {
        return stackTop - stack;
    }

    InterpretResult VirtualMachine::run(bool exitAtFirstReturn)
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
		#define READ_STRING() AS_STRING(*this, READ_CONSTANT())
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

        #ifdef DEBUG_LOG
        printStack();
        disassembleInstruction(&frame->function->chunk, (int)(frame->ip - frame->function->chunk.code.data()));
        #endif
        
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
                Value& top = peek(0);

                if (IS_OBJ_PTR(top))
                {
                    #ifdef DEBUG_LOG
                    std::cout << "Poping OBJ ptr : ";
                    printObject(top);
                    std::cout << std::endl;

                    std::cout << "refCount : " << unsigned(objectMemory.getHeader(AS_OBJ_PTR(top))->refCount) << std::endl;
                    #endif

                    objectMemory.free(AS_OBJ_PTR(top));
                }

                pop(1u);

                DISPATCH();
            }

            //TODO: remove this when static memory will be available
            CASES(OP_NR_POP)
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
                setValue(&(globals[READ_BYTE()]), peek(0));
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
                setValue(&(frame->slots[READ_BYTE()]), peek(0));
                pop(1u);

                DISPATCH();
            }

            CASES(OP_GET_PROPERTY)
            {
                assert(IS_INSTANCE(*this, peek(0)) || IS_CLASS(*this, peek(0)));

                uint16_t slot = READ_UINT16();

                Value* value = nullptr;

                if (IS_INSTANCE(*this, peek(0)))
                {
                    ObjInstance* instance = AS_INSTANCE(*this, peek(0));
                    value = instance->getField(*this, slot);
                }
                else
                {
                    ObjClass* klass = AS_CLASS(*this, peek(0));
                    value = klass->getStaticField(*this, slot);
                }

                pop(1u); // Instance or Class.
                push(*value);

                DISPATCH();
            }

            CASES(OP_SET_PROPERTY)
            {
                assert(IS_INSTANCE(*this, peek(0)) || IS_CLASS(*this, peek(0)));

                uint16_t slot = READ_UINT16();

                if (IS_INSTANCE(*this, peek(0)))
                {
                    ObjInstance* instance = AS_INSTANCE(*this, peek(0));
                    setValue(instance->getField(*this, slot), peek(1));
                }
                else
                {
                    ObjClass* klass = AS_CLASS(*this, peek(0));
                    setValue(klass->getStaticField(*this, slot), peek(1));
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
                if (!callNative(AS_GLOBAL_NATIVE(*this, peek(argCount)), argCount))
                {
                    return InterpretResult::INTERPRET_RUNTIME_ERROR;
                }

                frame = &frames[frameCount - 1];

                DISPATCH();
            }

            CASES(OP_CALL_GLOBAL)
            {
                uint16_t argCount = READ_UINT16();
                if (!call(AS_FUNCTION(*this, peek(argCount)), argCount))
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

                if (exitAtFirstReturn)
                {
                    return InterpretResult::INTERPRET_OK;
                }

                frame = &frames[frameCount - 1];

                DISPATCH();
            }

            CASES(OP_INHERIT)
            {
                assert(IS_CLASS(*this, peek(1)) && IS_CLASS(*this, peek(0)));

                ObjClass* klass = AS_CLASS(*this, peek(1));
                ObjClass* superclass = AS_CLASS(*this, peek(0));

                std::memcpy(klass->getStaticField(*this, 0u), superclass->getStaticField(*this, 0u), sizeof(Value) * klass->nmbStaticFields);
                klass->staticFieldsIndices = superclass->staticFieldsIndices;

                klass->fieldsIndices = superclass->fieldsIndices;

                std::memcpy(klass->getNativeMethod(*this, 0u), superclass->getNativeMethod(*this, 0u), sizeof(Value) * klass->nmbNativeMethods);
                klass->nativeMethodsIndices = superclass->nativeMethodsIndices;

                std::memcpy(klass->getMethod(*this, 0u), superclass->getMethod(*this, 0u), sizeof(Value) * klass->nmbMethods);
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
                uint16_t argCount = READ_UINT16();

                assert(IS_CLASS(*this, peek(0)));
                ObjClass* superclass = AS_CLASS(*this, pop());

                ObjBoundMethod bound(peek(argCount), (native) ? superclass->getNativeMethod(*this, slot) : superclass->getMethod(*this, slot));

                if (!callBoundMethod(bound, argCount))
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
                ObjString* name = READ_STRING();
                READ_64BITS(uint64_t, nmbMethods);
                READ_64BITS(uint64_t, nmbNativeMethods);
                READ_64BITS(uint64_t, nmbStaticFields);
                READ_64BITS(uint64_t, nmbFields);

                push(OBJ_PTR_VAL(newClass(name, nmbMethods, nmbNativeMethods, nmbStaticFields, nmbFields)->pointer));

                DISPATCH();
            }

            CASES(OP_NEW)
            {
                uint16_t argCount = READ_UINT16();
                bool foundConstructor = READ_BYTE();
                uint16_t slot = READ_UINT16();

                assert(IS_CLASS(*this, peek(argCount)));

                ObjClass* klass = AS_CLASS(*this, peek(argCount));
                stackTop[-argCount - 1] = OBJ_PTR_VAL(newInstance(klass)->pointer);

                if (foundConstructor)
                {
                    std::cout << "slot : " << unsigned(slot) << std::endl;
                    assert(IS_FUNCTION(*this, *(klass->getMethod(*this, slot))));

                    if (!call(AS_FUNCTION(*this, *(klass->getMethod(*this, slot))), argCount))
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

        return InterpretResult::INTERPRET_RUNTIME_ERROR;
    }

    bool VirtualMachine::isFalsey(const Value& value) const
    {
        if (IS_NULL(value)) return true;

        assert(IS_BOOL(value));

        return !AS_BOOL(value);
    }

    bool VirtualMachine::invoke(uint16_t argCount, uint16_t slot, bool native)
    {
        Value& parent = peek(argCount);

        ObjBoundMethod bound(parent, [&] () -> Value* {
            if (!IS_OBJ_PTR(parent))
                return (native) ? primitives[static_cast<uint8_t>(getPrimitiveTypeFromValue(parent))]->getNativeMethod(*this, slot) : primitives[static_cast<uint8_t>(getPrimitiveTypeFromValue(parent))]->getMethod(*this, slot);

            if (IS_INSTANCE(*this, parent))
            {
                ObjInstance* instance = AS_INSTANCE(*this, parent);
                return (native) ? instance->getNativeMethod(*this, slot) : instance->klass->getMethod(*this, slot);
            }

            assert(IS_CLASS(*this, parent));
            ObjClass* klass = AS_CLASS(*this, parent);
            return (native) ? klass->getNativeMethod(*this, slot) : klass->getMethod(*this, slot);
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
        if (IS_FUNCTION(*this, *bound.method))
        {
            stackTop[-argCount - 1] = bound.receiver;
            return call(AS_FUNCTION(*this, *bound.method), argCount);
        }

        Value result = [&] () {
            if (!IS_OBJ_PTR(bound.receiver))
            {
                MethodPrimitiveNativeFn& native = AS_METHOD_PRIMITIVE_NATIVE(*this, *bound.method);
                assert(native);

                return native(*this, argCount, &bound.receiver, stackTop - argCount);
            }

            MethodNativeFn& native = AS_METHOD_NATIVE(*this, *bound.method);
            assert(native);
            return native(*this, argCount, AS_INSTANCE(*this, bound.receiver), stackTop - argCount);
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

    void VirtualMachine::printValue(const Value& value) const
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
        else if (IS_OBJ_PTR(value))
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

    void VirtualMachine::printObject(const Value& value) const
    {
        switch (OBJ_TYPE(*this, value))
        {
            case ObjType::OBJ_BOUND_METHOD:
                printObject(*AS_BOUND_METHOD(*this, value)->method);
                break;
            case ObjType::OBJ_CLASS:
                std::cout << "class " << AS_CLASS(*this, value)->name->chars.c_str();
                break;
            case ObjType::OBJ_FUNCTION:
                printFunction(AS_FUNCTION(*this, value));
                break;
            case ObjType::OBJ_INSTANCE:
                std::cout << AS_INSTANCE(*this, value)->klass->name->chars.c_str() << " instance";
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
                std::cout << AS_CSTRING(*this, value);
                break;
        }
    }

    void VirtualMachine::printFunction(const ObjFunction* function) const
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
        #ifdef DEBUG_LOG
        std::cout << "VirtualMachine::defineMethod(" << slot << ", " << name->chars << ", " << isNative << ")" << std::endl;
        #endif

        assert(IS_OBJ_PTR(peek(0)));

        Value& method = peek(0);

        assert(IS_CLASS(*this, peek(1)));

        ObjClass* klass = AS_CLASS(*this, peek(1));

        if (isNative)
        {
            *(klass->getNativeMethod(*this, slot)) = method;
            klass->nativeMethodsIndices.emplace(name->chars, slot);
        }
        else
        {
            *(klass->getMethod(*this, slot)) = method;
            klass->methodsIndices.emplace(name->chars, slot);
        }

        pop(1u);
    }

    void VirtualMachine::defineField(uint16_t slot, ObjString* name, bool isStatic)
    {
        #ifdef DEBUG_LOG
        std::cout << "VirtualMachine::defineField(" << slot << ", " << name->chars << ", " << isStatic << ")" << std::endl;
        #endif

        Value& value = peek(0);
        assert(IS_CLASS(*this, peek(1)));

        ObjClass* klass = AS_CLASS(*this, peek(1));

        if (isStatic)
        {
            *(klass->getStaticField(*this, slot)) = value;
            klass->staticFieldsIndices.emplace(name->chars, slot);
        }
        else
        {
            //TODO: default fields
            //klass->defaultFields[slot] = value;
            klass->fieldsIndices.emplace(name->chars, slot);
        }
        
        pop(1u);
    }

    ObjClass* VirtualMachine::newClass(ObjString* name, uint64_t nmbMethods, uint64_t nmbNativeMethods, uint64_t nmbStaticFields, uint64_t nmbFields)
    {
        ObjClass* klass = allocateObject<ObjClass>();
        klass->name = name;
        klass->nmbMethods = nmbMethods;
        klass->nmbNativeMethods = nmbNativeMethods;
        klass->nmbStaticFields = nmbStaticFields;
        klass->nmbFields = nmbFields;

        if (klass->nmbMethods > 0)
        {
            klass->methods = objectMemory.malloc(sizeof(Value) * klass->nmbMethods);
        }

        if (klass->nmbNativeMethods > 0)
        {
            klass->nativeMethods = objectMemory.malloc(sizeof(Value) * klass->nmbNativeMethods);
        }

        if (klass->nmbStaticFields > 0)
        {
            klass->staticFields = objectMemory.malloc(sizeof(Value) * klass->nmbStaticFields);
        }

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
        ObjInstance* instance = allocateObject<ObjInstance>();
        instance->klass = klass;

        if (klass->nmbFields > 0)
        {
            instance->fields = objectMemory.malloc(sizeof(Value) * klass->nmbFields);
        }

        if (klass->nmbNativeMethods > 0)
        {
            instance->nativeMethods = objectMemory.malloc(sizeof(Value) * klass->nmbNativeMethods);
            std::memcpy(instance->getNativeMethod(*this, 0u), klass->getNativeMethod(*this, 0u), sizeof(Value) * klass->nmbNativeMethods);
        }

        return instance;
    }

    ObjBoundMethod* VirtualMachine::newBoundMethod(const Value& receiver, Value* method)
    {
        ObjBoundMethod* bound = allocateObject<ObjBoundMethod>();
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
            case AS_OPCODE(OpCode::OP_NR_POP):
                return simpleInstruction("OP_NR_POP", offset);
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

    void VirtualMachine::setValue(Value* dest, const Value& src)
    {
        #ifdef DEBUG_LOG
        std::cout << "VirtualMachine::setValue" << std::endl;
        #endif

        if (IS_OBJ_PTR(*dest))
        {
            objectMemory.free(AS_OBJ_PTR(*dest));
        }

        *dest = src;

        if (IS_OBJ_PTR(src))
        {
            objectMemory.incRefCount(AS_OBJ_PTR(src));
        }

        #ifdef DEBUG_LOG
        std::cout << "End VirtualMachine::setValue" << std::endl;
        #endif
    }
}
