#pragma once

#include "Chunk.h"
#include "Object.h"
#include "Common.h"
#include "Memory.h"

#include <array>
#include <unordered_map>
#include <optional>

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)
#define GLOBALS_MAX UINT16_COUNT

//#define DEBUG_STRESS_GC
//#define DEBUG_LOG_GC

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

		bool linkGlobalNative(const std::string& name, GlobalNativeFn function);
		bool linkMethodNative(const std::string& className, const std::string& methodName, MethodNativeFn function);
		bool linkMethodNative(const std::string& className, const std::string& methodName, MethodPrimitiveNativeFn function);

		Value* getStaticField(const std::string& className, const std::string& fieldName);

		template<typename ... Strings>
		std::string getFunctionName(std::string name, const Strings&... rest)
		{
			return name + NAME_FUNC_SEPARATOR + getParametersType(rest...);
		}

		void push(const Value& value);
		Value pop();
		Value peek(int depth);

		template<typename T>
		T* allocateObject(ObjType type)
		{
			#ifdef DEBUG_STRESS_GC
			collectGarbage();
			#endif

			#ifndef DEBUG_STRESS_GC
			if (started && bytesAllocated > nextGC)
			{
				collectGarbage();
			}
			#endif

			#ifndef DEBUG_STRESS_GC
			bytesAllocated += sizeof(T);
			#endif

			#ifdef DEBUG_LOG_GC
			std::cout << "allocate " << sizeof(T) << " for " << ObjTypeToCStr(type) << std::endl;
			#endif

			T* t = new T();
			Obj* object = static_cast<Obj*>(t);
			object->type = type;
			object->isMarked = false;

			object->next = objects;
			objects = object;

			return t;
		}

		ObjString* newString();
		ObjString* copyString(const char* chars, int length);

		ObjPrimitive<int64_t>* newInt(uint64_t value);
		ObjPrimitive<double>* newFloat(double value);
		ObjPrimitive<bool>* newBool(bool value);

		ObjInstance* newInstance(const std::string& className);
		ObjInstance* newInstance(uint16_t slot);

		ObjFunction* newFunction();
		ObjGlobalNative* newGlobalNative();
		ObjMethodNative* newMethodNative();
		ObjMethodPrimitiveNative* newMethodPrimitiveNative();

		std::size_t addGlobal(const std::string& name);
		std::optional<std::size_t> getGlobal(const std::string& name);

		void printStack();
		int stackSize();

		void printValue(const Value& value);

		bool started;
		
	private:
		InterpretResult run();

		std::string getParametersType()
		{
			return "";
		}

		template<typename ... Strings>
		std::string getParametersType(std::string first, const Strings&... rest)
		{
			return first + HEADER_FUNC_SEPARATOR + getParametersType(rest...);
		}

		void freeObject(Obj* object);

		bool isFalsey(Value value);

		Obj* getMethod(int peekDepth, uint16_t slot, bool native);

		bool invoke(int argCount, uint16_t slot, bool native);
		bool callValue(const Value& callee, int argCount);
		bool call(ObjFunction* function, int argCount);

		void printObject(const Value& value);
		void printFunction(ObjFunction* function);

		void defineMethod(uint16_t slot, ObjString* name, bool isNative);
		void defineField(uint16_t slot, ObjString* name, bool isStatic);

		ObjClass* newClass(ObjString* name);
		ObjInstance* newInstance(ObjClass* klass);
		ObjBoundMethod* newBoundMethod(const Value& receiver, Value* method);

		template<typename T>
		ObjPrimitive<T>* newPrimitive(PrimitiveType type, T value)
		{
			ObjPrimitive<T>* primitive = new ObjPrimitive<T>();
			primitive->primitiveType = type;
			primitive->value = value;

			return primitive;
		}

		int disassembleInstruction(Chunk* chunk, int offset);
		int simpleInstruction(const char* name, int offset);
		int constantInstruction(const char* name, Chunk* chunk, int offset);
		int byteInstruction(const char* name, Chunk* chunk, int offset);
		int jumpInstruction(const char* name, int sign, Chunk* chunk, int offset);

		void collectGarbage();
		void markRoots();
		void markValue(Value& value);
		void markObject(Obj* object);
		void markArray(Value* array, std::size_t count);
		void traceReferences();
		void blackenObject(Obj* object);
		void sweep();

	private:
		CallFrame frames[FRAMES_MAX];
  		int frameCount;

		Value stack[STACK_MAX];
		Value* stackTop;

		std::unordered_map<std::string, std::size_t> globalsIndices;
		std::size_t globalsIndicesCount;

		Value globals[GLOBALS_MAX];

		Obj* objects;

		ObjClass* primitives[static_cast<uint8_t>(PrimitiveType::COUNT)];

		std::vector<Obj*> grayStack;

		std::size_t bytesAllocated;
  		std::size_t nextGC;
	};
}