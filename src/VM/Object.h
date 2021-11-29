#pragma once

#include <cstdint>
#include <string>
#include <functional>
#include <cstring>
#include <variant>
#include <cassert>

#include "Value.h"
#include "Chunk.h"

#define FIELDS_MAX 256
#define METHODS_MAX 256

namespace Pomme
{
    #define OBJ_TYPE(value)        (value.asObj()->type)

    #define IS_BOUND_METHOD(value)              isObjType(value, ObjType::OBJ_BOUND_METHOD)
    #define IS_CLASS(value)                     isObjType(value, ObjType::OBJ_CLASS)
    #define IS_FUNCTION(value)                  isObjType(value, ObjType::OBJ_FUNCTION)
    #define IS_INSTANCE(value)                  isObjType(value, ObjType::OBJ_INSTANCE)
    #define IS_GLOBAL_NATIVE(value)             isObjType(value, ObjType::OBJ_GLOBAL_NATIVE)
    #define IS_METHOD_NATIVE(value)             isObjType(value, ObjType::OBJ_METHOD_NATIVE)
    #define IS_METHOD_PRIMITIVE_NATIVE(value)   isObjType(value, ObjType::OBJ_METHOD_PRIMITIVE_NATIVE)
    #define IS_STRING(value)                    isObjType(value, ObjType::OBJ_STRING)

    #define AS_BOUND_METHOD(value) (static_cast<ObjBoundMethod*>((value).asObj()))
    #define AS_CLASS(value)        (static_cast<ObjClass*>((value).asObj()))
    #define AS_FUNCTION(value)     (static_cast<ObjFunction*>((value).asObj()))
    #define AS_INSTANCE(value)     (static_cast<ObjInstance*>((value).asObj()))
    #define AS_GLOBAL_NATIVE(value) \
        (static_cast<ObjGlobalNative*>((value).asObj())->function)
    #define AS_METHOD_NATIVE(value) \
        (static_cast<ObjMethodNative*>((value).asObj())->function)
    #define AS_METHOD_PRIMITIVE_NATIVE(value) \
        (static_cast<ObjMethodPrimitiveNative*>((value).asObj())->function)
    #define AS_STRING(value)       (static_cast<ObjString*>((value).asObj()))
    #define AS_CSTRING(value)      (AS_STRING(value)->chars.c_str())

    enum class ObjType: uint8_t
    {
        OBJ_BOUND_METHOD,
        OBJ_CLASS,
        OBJ_FUNCTION,
        OBJ_INSTANCE,
        OBJ_GLOBAL_NATIVE,
        OBJ_METHOD_NATIVE,
        OBJ_METHOD_PRIMITIVE_NATIVE,
        OBJ_STRING,
    };

    const char* ObjTypeToCStr(ObjType type);

    struct Obj
    {
        ObjType type;
        bool isMarked;
        Obj* next;

        virtual ~Obj() = default;

        inline bool isType(ObjType objType) {return type == objType;}
    };

    struct ObjString: public Obj
    {
        std::string chars;
    };

    struct ObjFunction: public Obj
    {
        uint16_t arity;
        Chunk chunk;
        ObjString* name;
    };

    struct ObjInstance;

    using GlobalNativeFn = std::function<Value(VirtualMachine&, int, Value*)>;
    using MethodNativeFn = std::function<Value(VirtualMachine&, int, ObjInstance*, Value*)>;
    using MethodPrimitiveNativeFn = std::function<Value(VirtualMachine&, int, ObjPrimitive*, Value*)>;

    struct ObjGlobalNative: public Obj
    {
        GlobalNativeFn function;
    };

    struct ObjMethodNative: public Obj
    {
        MethodNativeFn function;
    };

    struct ObjMethodPrimitiveNative: public Obj
    {
        MethodPrimitiveNativeFn function;
    };

    struct ObjClass : public Obj
    {
        //Runtime
        ObjString* name;
        Value methods[METHODS_MAX]; 
        Value nativeMethods[METHODS_MAX];
        Value staticFields[FIELDS_MAX]; 
        Value defaultFields[FIELDS_MAX];
        
        int deconstructorIdx = -1;

        Value* getStaticField(const std::string& name);

        //Used for C++->Pomme call
        std::unordered_map<std::string, uint16_t> methodsIndices;
        std::unordered_map<std::string, uint16_t> nativeMethodsIndices;
        std::unordered_map<std::string, uint16_t> fieldsIndices;
        std::unordered_map<std::string, uint16_t> staticFieldsIndices;
    };

    struct ObjInstance: public Obj
    {
        ObjClass* klass;
        Value fields[FIELDS_MAX];
        Value nativeMethods[METHODS_MAX];

        Value* getField(const std::string& name);
        Value* getStaticField(const std::string& name);

        bool linkMethodNative(const std::string& methodName, MethodNativeFn function);
    };

    struct PommeString
    {
        ObjString* value;

        PommeString(VirtualMachine& vm, ObjInstance* instance);

        Value pommeOperatorPlus(VirtualMachine& vm, int argcount, ObjInstance* instance, Value* args);
    };

    struct ObjBoundMethod: public Obj
    {
        ObjBoundMethod() = default;
        
        ObjBoundMethod(Value receiv, Value* meth)
        : receiver(std::move(receiv))
        , method(meth)
        {
        }

        Value receiver;
        Value* method;
    };
    
    static inline bool isObjType(const Value& value, ObjType type)
    {
        return value.isObj() && value.asObj()->isType(type);
    }
}