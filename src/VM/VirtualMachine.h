#pragma once

#include "Chunk.h"
#include "Object.h"

#include <array>
#include <unordered_map>

#define UINT8_COUNT (UINT8_MAX + 1)
#define UINT16_COUNT (UINT16_MAX + 1)

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)
#define GLOBALS_MAX UINT16_COUNT

namespace Pomme
{

	#define ALLOCATE(vm, type, count) \
        reinterpret_cast<type*>(vm->reallocate(NULL, 0, sizeof(type) * (count)))
    
    #define ALLOCATE_OBJ(vm, type, objectType) \
        reinterpret_cast<type*>(vm->allocateObject(sizeof(type), objectType))

	#define FREE_ARRAY(type, pointer, oldCount) \
    	reallocate(pointer, sizeof(type) * (oldCount), 0)

	#define FREE(type, pointer) reallocate(pointer, sizeof(type), 0)


	enum class InterpretResult: uint8_t
	{
		INTERPRET_OK,
		INTERPRET_RUNTIME_ERROR,
	};

	struct CallFrame
	{
		ObjFunction* function;
		uint8_t* ip;
		Value* slots;
	};

	class VirtualMachine
	{
	public:
		VirtualMachine();
		~VirtualMachine();

		InterpretResult interpret(ObjFunction* function);

		void defineGlobalNative(std::string name, NativeFn function);

		void push(Value value);
		Value pop();
		Value peek(int depth);

		void* reallocate(void* pointer, size_t oldSize, size_t newSize);
		Obj* allocateObject(size_t size, ObjType type);

		ObjString* allocateString(char* chars, int length);
		ObjString* copyString(const char* chars, int length);
		
	private:
		InterpretResult run();

		void freeObject(Obj* object);

		bool isFalsey(Value value);

		bool callValue(Value callee, int argCount);
		bool call(ObjFunction* function, int argCount);

		void printValue(Value value);
		void printObject(Value value);
		void printFunction(ObjFunction* function);

		void defineMethod(uint16_t slot, ObjString* name);
		void defineField(uint16_t slot, ObjString* name);

		ObjInstance* newInstance(ObjClass* klass);
		ObjBoundMethod* newBoundMethod(Value receiver, ObjFunction* method);

	private:
		std::array<CallFrame, FRAMES_MAX> frames;
  		int frameCount;

		std::array<Value, STACK_MAX> stack;
		Value* stackTop;

		std::array<Value, GLOBALS_MAX> globals;

		Obj* objects;
	};

	static void* reallocate(void* pointer, size_t oldSize, size_t newSize)
    {
        if (newSize == 0)
        {
            free(pointer);
            return NULL;
        }

        void* result = std::realloc(pointer, newSize);
        return result;
    }
}