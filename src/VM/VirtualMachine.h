#pragma once

#include "Chunk.h"
#include "Object.h"
#include "Common.h"

#include <array>
#include <unordered_map>

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)
#define GLOBALS_MAX UINT16_COUNT

namespace Pomme
{
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
		InterpretResult interpretGlobalFunction(const std::string& name);

		void defineGlobalNative(std::string name, NativeFn function);

		void push(Value value);
		Value pop();
		Value peek(int depth);

		Obj* allocateObject(size_t size, ObjType type);

		ObjString* allocateString(char* chars, int length);
		ObjString* copyString(const char* chars, int length);

		ObjFunction* newFunction();

		std::size_t addGlobal(const std::string& name);
		
	private:
		InterpretResult run();

		void freeObject(Obj* object);

		bool isFalsey(Value value);

		bool valuesEqual(Value a, Value b);

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

		std::unordered_map<std::string, std::size_t> globalsIndices;
		std::size_t globalsIndicesCount;

		std::array<Value, GLOBALS_MAX> globals;

		Obj* objects;
	};
}