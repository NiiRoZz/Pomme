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
			T* t = new T();
			Obj* object = static_cast<Obj*>(t);
			object->type = type;

			object->next = objects;
			objects = object;

			return t;
		}

		ObjString* newString();
		ObjString* copyString(const char* chars, int length);

		ObjPrimitive* newInt(uint64_t value);
		ObjPrimitive* newFloat(double value);
		ObjPrimitive* newBool(bool value);

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
		ObjPrimitive* newPrimitive(ObjClass* klass, PrimitiveType type, T value)
		{
			ObjPrimitive* primitive = ALLOCATE_OBJ(this, ObjPrimitive, ObjType::OBJ_PRIMITIVE);
			primitive->klass = klass;
			primitive->primitiveType = type;
			primitive->value = value;

			return primitive;
		}

		int disassembleInstruction(Chunk* chunk, int offset);
		int simpleInstruction(const char* name, int offset);
		int constantInstruction(const char* name, Chunk* chunk, int offset);
		int byteInstruction(const char* name, Chunk* chunk, int offset);
		int jumpInstruction(const char* name, int sign, Chunk* chunk, int offset);

	private:
		CallFrame frames[FRAMES_MAX];
  		int frameCount;

		Value stack[STACK_MAX];
		Value* stackTop;

		std::unordered_map<std::string, std::size_t> globalsIndices;
		std::size_t globalsIndicesCount;

		Value globals[GLOBALS_MAX];

		Obj* objects;

		ObjClass* intClass;
		ObjClass* floatClass;
		ObjClass* boolClass;
		ObjClass* stringClass;
	};
}