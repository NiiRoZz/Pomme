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

		InterpretResult interpret(ObjFunction* function);

		void defineGlobalNative(std::string name, NativeFn function);

		void push(Value value);
		Value pop();
		Value peek(int depth);
		
	private:
		InterpretResult run();

		bool isFalsey(Value value);

		bool callValue(Value callee, int argCount);
		bool call(ObjFunction* function, int argCount);

		void printValue(Value value);
		void printObject(Value value);
		void printFunction(ObjFunction* function);

	private:
		std::array<CallFrame, FRAMES_MAX> frames;
  		int frameCount;

		std::array<Value, STACK_MAX> stack;
		Value* stackTop;

		std::array<Value, GLOBALS_MAX> globals;
	};
}