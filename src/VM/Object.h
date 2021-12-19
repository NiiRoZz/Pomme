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
    #define OBJ_TYPE(vm, value)                     (AS_OBJ(vm, value)->type)

    #define IS_BOUND_METHOD(vm, value)              isObjType(vm, value, ObjType::OBJ_BOUND_METHOD)
    #define IS_CLASS(vm, value)                     isObjType(vm, value, ObjType::OBJ_CLASS)
    #define IS_FUNCTION(vm, value)                  isObjType(vm, value, ObjType::OBJ_FUNCTION)
    #define IS_INSTANCE(vm, value)                  isObjType(vm, value, ObjType::OBJ_INSTANCE)
    #define IS_GLOBAL_NATIVE(vm, value)             isObjType(vm, value, ObjType::OBJ_GLOBAL_NATIVE)
    #define IS_METHOD_NATIVE(vm, value)             isObjType(vm, value, ObjType::OBJ_METHOD_NATIVE)
    #define IS_METHOD_PRIMITIVE_NATIVE(vm, value)   isObjType(vm, value, ObjType::OBJ_METHOD_PRIMITIVE_NATIVE)
    #define IS_STRING(vm, value)                    isObjType(vm, value, ObjType::OBJ_STRING)

    #define AS_BOUND_METHOD(vm, value)                  (static_cast<ObjBoundMethod*>(AS_OBJ(vm, value)))
    #define AS_CLASS(vm, value)                         (static_cast<ObjClass*>(AS_OBJ(vm, value)))
    #define AS_FUNCTION(vm, value)                      (static_cast<ObjFunction*>(AS_OBJ(vm, value)))
    #define AS_INSTANCE(vm, value)                      (static_cast<ObjInstance*>(AS_OBJ(vm, value)))
    #define AS_GLOBAL_NATIVE(vm, value)                 (static_cast<ObjGlobalNative*>(AS_OBJ(vm, value))->function)
    #define AS_METHOD_NATIVE(vm, value)                 (static_cast<ObjMethodNative*>(AS_OBJ(vm, value))->function)
    #define AS_METHOD_PRIMITIVE_NATIVE(vm, value)       (static_cast<ObjMethodPrimitiveNative*>(AS_OBJ(vm, value))->function)
    #define AS_STRING(vm, value)                        (static_cast<ObjString*>(AS_OBJ(vm, value)))
    #define AS_CSTRING(vm, value)                       (AS_STRING(vm, value)->chars.c_str())

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
        virtual ~Obj() = default;

        inline bool isType(ObjType objType) const {return type == objType;}

        ObjType type;
        Pointer pointer;
    };

    struct ObjString: public Obj
    {
        virtual ~ObjString() = default;

        std::string chars;
    };

    struct ObjFunction: public Obj
    {
        virtual ~ObjFunction() = default;

        uint16_t arity;
        Chunk chunk;
        ObjString* name;
    };

    struct ObjInstance;

    using GlobalNativeFn = std::function<Value(VirtualMachine&, int, Value*)>;
    using MethodNativeFn = std::function<Value(VirtualMachine&, int, ObjInstance*, Value*)>;

    using MethodPrimitiveNativeFn = std::function<Value(VirtualMachine&, int, Value*, Value*)>;

    struct ObjGlobalNative: public Obj
    {
        virtual ~ObjGlobalNative() = default;

        GlobalNativeFn function;
    };

    struct ObjMethodNative: public Obj
    {
        virtual ~ObjMethodNative() = default;

        MethodNativeFn function;
    };

    struct ObjMethodPrimitiveNative: public Obj
    {
        virtual ~ObjMethodPrimitiveNative() = default;

        MethodPrimitiveNativeFn function;
    };

    struct ObjClass : public Obj
    {
        virtual ~ObjClass() = default;

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
        virtual ~ObjInstance() = default;

        ObjClass* klass;
        Value fields[FIELDS_MAX];
        Value nativeMethods[METHODS_MAX];

        Value* getField(const std::string& name);
        Value* getStaticField(const std::string& name);

        bool linkMethodNative(const std::string& methodName, MethodNativeFn function);
    };

    struct ObjBoundMethod: public Obj
    {
        virtual ~ObjBoundMethod() = default;

        ObjBoundMethod() = default;
        
        ObjBoundMethod(Value receiv, Value* meth)
        : receiver(std::move(receiv))
        , method(meth)
        {
        }

        Value receiver;
        Value* method;
    };
    
    class VirtualMachine;

    bool isObjType(const VirtualMachine& vm, const Value& value, ObjType type);

    template<typename T>
    static constexpr ObjType getObjType()
    {
        if constexpr (std::is_same_v<T, Obj>)
        {
            return ObjType::OBJ_BOUND_METHOD;
        }
        else if constexpr (std::is_same_v<T, ObjString>)
        {
            return ObjType::OBJ_STRING;
        }
        else if constexpr (std::is_same_v<T, ObjFunction>)
        {
            return ObjType::OBJ_FUNCTION;
        }
        else if constexpr (std::is_same_v<T, ObjGlobalNative>)
        {
            return ObjType::OBJ_GLOBAL_NATIVE;
        }
        else if constexpr (std::is_same_v<T, ObjMethodNative>)
        {
            return ObjType::OBJ_METHOD_NATIVE;
        }
        else if constexpr (std::is_same_v<T, ObjMethodPrimitiveNative>)
        {
            return ObjType::OBJ_METHOD_PRIMITIVE_NATIVE;
        }
        else if constexpr (std::is_same_v<T, ObjClass>)
        {
            return ObjType::OBJ_CLASS;
        }
        else if constexpr (std::is_same_v<T, ObjInstance>)
        {
            return ObjType::OBJ_INSTANCE;
        }
        else if constexpr (std::is_same_v<T, ObjBoundMethod>)
        {
            return ObjType::OBJ_BOUND_METHOD;
        }
        else if constexpr (true)
        {
            assert(false && "Can't get ObjType from template");
        }
    }
}