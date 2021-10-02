#pragma once

#include <cstdint>
#include <string>
#include <functional>

#include "Value.h"
#include "Chunk.h"

#define FIELDS_MAX 256
#define METHODS_MAX 256

namespace Pomme
{
    #define ALLOCATE_OBJ(type, objectType) \
        (type*)allocateObject(sizeof(type), objectType)

    #define OBJ_TYPE(value)        (AS_OBJ(value)->type)

    #define IS_BOUND_METHOD(value) isObjType(value, OBJ_BOUND_METHOD)
    #define IS_CLASS(value)        isObjType(value, OBJ_CLASS)
    #define IS_FUNCTION(value)     isObjType(value, OBJ_FUNCTION)
    #define IS_INSTANCE(value)     isObjType(value, OBJ_INSTANCE)
    #define IS_NATIVE(value)       isObjType(value, OBJ_NATIVE)
    #define IS_STRING(value)       isObjType(value, OBJ_STRING)

    #define AS_BOUND_METHOD(value) ((ObjBoundMethod*)AS_OBJ(value))
    #define AS_CLASS(value)        ((ObjClass*)AS_OBJ(value))
    #define AS_FUNCTION(value)     ((ObjFunction*)AS_OBJ(value))
    #define AS_INSTANCE(value)     ((ObjInstance*)AS_OBJ(value))
    #define AS_NATIVE(value) \
        (((ObjNative*)AS_OBJ(value))->function)
    #define AS_STRING(value)       ((ObjString*)AS_OBJ(value))
    #define AS_STDSTRING(value)      (((ObjString*)AS_OBJ(value))->chars)

    enum class ObjType: uint8_t
    {
        OBJ_BOUND_METHOD,
        OBJ_CLASS,
        OBJ_FUNCTION,
        OBJ_INSTANCE,
        OBJ_NATIVE,
        OBJ_STRING,
    };

    struct Obj
    {
        ObjType type;
    };

    struct ObjString
    {
        Obj obj;
        std::string chars;
    };

    using NativeFn = std::function<Value(int, Value*)>;

    struct ObjNative
    {
        Obj obj;
        NativeFn function;
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
        Obj obj;
        ObjString* name;
        std::array<Value, METHODS_MAX> methods; 
        int constructorIdx = -1;
        int deconstructorIdx = -1;
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

    static Obj* allocateObject(size_t size, ObjType type)
    {
        Obj* object = (Obj*)reallocate(NULL, 0, size);
        object->type = type;
        return object;
    }
}