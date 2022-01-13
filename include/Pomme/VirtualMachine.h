#pragma once

#include "Chunk.h"
#include "Object.h"
#include "Common.h"
#include "ObjectMemory.h"

#include <array>
#include <unordered_map>
#include <optional>

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)
#define GLOBALS_MAX UINT16_COUNT

#define DEBUG_LOG

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
		InterpretResult interpretGlobalFunction(const std::string& name, const std::vector<Value>& params);
		InterpretResult interpretMethodFunction(ObjInstance* instance, const std::string& methodName, const std::vector<Value>& params);

		std::optional<Value> callGlobalFunction(const std::string& name, const std::vector<Value>& params);
		std::optional<Value> callMethodFunction(ObjInstance* instance, const std::string& methodName, const std::vector<Value>& params);

		bool linkStdNative();
		
		bool linkGlobalNative(const std::string& name, GlobalNativeFn function);
		bool linkMethodNative(const std::string& className, const std::string& methodName, MethodNativeFn function);
		bool linkMethodNative(const std::string& className, const std::string& methodName, MethodPrimitiveNativeFn function);

		Value* getStaticField(const std::string& className, const std::string& fieldName) const;

		template<typename ... Strings>
		std::string getFunctionName(std::string name, const Strings&... rest) const
		{
			return name + NAME_FUNC_SEPARATOR + getParametersType(rest...);
		}

		template<typename T, typename ...Args>
		inline T* allocateObject(Args&& ...args)
		{
			static_assert(std::is_base_of<Obj, T>::value, "You should allocate something that inherit from Obj class");
			return objectMemory.allocObject<T>(std::forward<Args>(args)...);
		}

		template<typename T>
        inline T* getObject(Pointer p) const
        {
            return objectMemory.get<T>(p);
        }

		ObjString* newString();
		ObjString* copyString(const char* chars, int length);

		ObjInstance* newInstance(const std::string& className);
		ObjInstance* newInstance(uint16_t slot);

		ObjFunction* newFunction();
		ObjGlobalNative* newGlobalNative();
		ObjMethodNative* newMethodNative();
		ObjMethodPrimitiveNative* newMethodPrimitiveNative();

		std::size_t addGlobal(const std::string& name);
		std::optional<std::size_t> getGlobal(const std::string& name) const;

		void printStack();
		int stackSize() const;

		void printValue(const Value& value) const;
		
	private:
		InterpretResult run(bool exitAtFirstReturn = false);

		std::string getParametersType() const
		{
			return "";
		}

		template<typename ... Strings>
		std::string getParametersType(std::string first, const Strings&... rest) const
		{
			return first + HEADER_FUNC_SEPARATOR + getParametersType(rest...);
		}

		bool isFalsey(const Value& value) const;

		bool invoke(uint16_t argCount, uint16_t slot, bool native);
		bool callNative(GlobalNativeFn& nativeFn, uint16_t argCount);
		bool callBoundMethod(ObjBoundMethod& bound, uint16_t argCount);
		bool call(ObjFunction* function, uint16_t argCount);

		void printObject(const Value& value) const;
		void printFunction(const ObjFunction* function) const;

		void defineMethod(uint16_t slot, ObjString* name, bool isNative);
		void defineField(uint16_t slot, ObjString* name, bool isStatic);

		ObjClass* newClass(ObjString* name, uint64_t nmbMethods, uint64_t nmbNativeMethods, uint64_t nmbStaticFields, uint64_t nmbFields);
		ObjInstance* newInstance(ObjClass* klass);
		ObjBoundMethod* newBoundMethod(const Value& receiver, Value* method);

		int disassembleInstruction(Chunk* chunk, int offset);
		int simpleInstruction(const char* name, int offset);
		int constantInstruction(const char* name, Chunk* chunk, int offset);
		int byteInstruction(const char* name, Chunk* chunk, int offset);
		int jumpInstruction(const char* name, int sign, Chunk* chunk, int offset);

		void setValue(Value* dest, const Value& src);

		inline void push(const Value& value)
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

		inline void push(Value&& value)
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

		inline Value pop()
		{
			stackTop--;
  			return *stackTop;
		}

		inline void drop(int depth)
		{
			stackTop -= depth;
		}

		inline Value& peek(int depth) const
		{
			return stackTop[-1 - depth];
		}

	private:
		CallFrame frames[FRAMES_MAX];
  		std::size_t frameCount;

		Value stack[STACK_MAX];
		Value* stackTop;

		std::unordered_map<std::string, std::size_t> globalsIndices;
		std::size_t globalsIndicesCount;

		Value globals[GLOBALS_MAX];

		ObjClass* primitives[static_cast<uint8_t>(PrimitiveType::COUNT)];

		ObjectMemory objectMemory;
	};
}