#pragma once

#include <cstdint>
#include <string>
#include <functional>
#include <cstring>

#include "Value.h"
#include "Chunk.h"

#define FIELDS_MAX 256
#define METHODS_MAX 256

namespace Pomme
{
    #define OBJ_TYPE(value)        (AS_OBJ(value)->type)

    #define IS_BOUND_METHOD(value)  isObjType(value, ObjType::OBJ_BOUND_METHOD)
    #define IS_CLASS(value)         isObjType(value, ObjType::OBJ_CLASS)
    #define IS_FUNCTION(value)      isObjType(value, ObjType::OBJ_FUNCTION)
    #define IS_INSTANCE(value)      isObjType(value, ObjType::OBJ_INSTANCE)
    #define IS_GLOBAL_NATIVE(value) isObjType(value, ObjType::OBJ_GLOBAL_NATIVE)
    #define IS_STRING(value)        isObjType(value, ObjType::OBJ_STRING)

    #define AS_BOUND_METHOD(value) ((ObjBoundMethod*)AS_OBJ(value))
    #define AS_CLASS(value)        ((ObjClass*)AS_OBJ(value))
    #define AS_FUNCTION(value)     ((ObjFunction*)AS_OBJ(value))
    #define AS_INSTANCE(value)     ((ObjInstance*)AS_OBJ(value))
    #define AS_GLOBAL_NATIVE(value) \
        (((ObjNative*)AS_OBJ(value))->function)
    #define AS_STRING(value)       ((ObjString*)AS_OBJ(value))
    #define AS_CSTRING(value)      (((ObjString*)AS_OBJ(value))->chars)

    enum class ObjType: uint8_t
    {
        OBJ_BOUND_METHOD,
        OBJ_CLASS,
        OBJ_FUNCTION,
        OBJ_INSTANCE,
        OBJ_GLOBAL_NATIVE,
        OBJ_STRING,
    };

    struct Obj
    {
        ObjType type;
        Obj* next;
    };

    struct ObjString
    {
        Obj obj;
        int length;
        char* chars;
    };

    using GlobalNativeFn = std::function<Value(int, Value*)>;

    struct ObjNative
    {
        Obj obj;
        GlobalNativeFn function;
    };

    struct ObjFunction
    {
        Obj obj;
        int arity;
        Chunk chunk;
        ObjString* name;
    };

    struct ObjClass
    {
        //Runtime
        Obj obj;
        ObjString* name;
        std::array<Value, METHODS_MAX> methods; 
        int deconstructorIdx = -1;

        //Used for C++->Pomme call
        std::unordered_map<std::string, uint16_t> methodsIndices;
        std::unordered_map<std::string, uint16_t> fieldsIndices;
    };

    struct ObjInstance
    {
        Obj obj;
        ObjClass* klass;
        std::array<Value, FIELDS_MAX> fields; 
    };

    struct ObjBoundMethod
    {
        Obj obj;
        Value receiver;
        ObjFunction* method;
    };

    static inline bool isObjType(Value value, ObjType type)
    {
        return IS_OBJ(value) && AS_OBJ(value)->type == type;
    }
}