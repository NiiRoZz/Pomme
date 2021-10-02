#pragma once

#include <cstdint>
#include <string>
#include <functional>

#include "Value.h"
#include "Chunk.h"

namespace Pomme
{
    #define OBJ_TYPE(value)        (AS_OBJ(value)->type)

    #define IS_FUNCTION(value)     isObjType(value, OBJ_FUNCTION)
    #define IS_NATIVE(value)       isObjType(value, OBJ_NATIVE)
    #define IS_STRING(value)       isObjType(value, OBJ_STRING)

    #define AS_FUNCTION(value)     ((ObjFunction*)AS_OBJ(value))
    #define AS_NATIVE(value) \
        (((ObjNative*)AS_OBJ(value))->function)
    #define AS_STRING(value)       ((ObjString*)AS_OBJ(value))
    #define AS_STDSTRING(value)      (((ObjString*)AS_OBJ(value))->chars)

    enum class ObjType: uint8_t
    {
        OBJ_FUNCTION,
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

    static inline bool isObjType(Value value, ObjType type)
    {
        return IS_OBJ(value) && AS_OBJ(value)->type == type;
    }
}