#pragma once

#include <cstdint>

namespace Pomme
{
    typedef struct Obj Obj;
    typedef struct ObjString ObjString;

    enum class ValueType: uint8_t
    {
        VAL_NULL,
        VAL_OBJ,
    };

    struct Value
    {
        ValueType type;
        Obj* obj;
    };

    #define IS_NULL(value)          ((value).type == ValueType::VAL_NULL)
    #define IS_OBJ(value)           ((value).type == ValueType::VAL_OBJ)

    #define AS_OBJ(value)           ((value).obj)

    #define BOOL_VAL(vm, value)     (OBJ_VAL(vm.newBool(value)))
    #define INT_VAL(vm, value)      (OBJ_VAL(vm.newInt(value)))
    #define FLOAT_VAL(vm, value)    (OBJ_VAL(vm.newFloat(value)))
    #define NULL_VAL                ((Value){ValueType::VAL_NULL, nullptr})
    #define OBJ_VAL(object)         ((Value){ValueType::VAL_OBJ, static_cast<Obj*>(object)})
}