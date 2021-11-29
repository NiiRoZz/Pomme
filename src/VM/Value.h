#pragma once

#include <cstdint>

namespace Pomme
{
    typedef struct Obj Obj;
    typedef struct ObjPrimitiveType ObjPrimitiveType;

    enum class ValueType: uint8_t
    {
        VAL_NULL,
        VAL_OBJ,
        VAL_PRIMITIVE,
    };

    struct Value
    {
        ValueType type;

        union
        {
            Obj* obj;
            ObjPrimitiveType* primitive;
        } as;
    };

    #define IS_NULL(value)          ((value).type == ValueType::VAL_NULL)
    #define IS_OBJ(value)           ((value).type == ValueType::VAL_OBJ)
    #define IS_PRIMITIVE(value)     ((value).type == ValueType::VAL_PRIMITIVE)

    #define AS_OBJ(value)           ((value).as.obj)
    #define AS_PRIMITIVE(value)     ((value).as.primitive)

    #define BOOL_VAL(vm, value)     (PrimitiveVal(vm.newBool(value)))
    #define INT_VAL(vm, value)      (PrimitiveVal(vm.newInt(value)))
    #define FLOAT_VAL(vm, value)    (PrimitiveVal(vm.newFloat(value)))
    #define NULL_VAL                ((Value){ValueType::VAL_NULL, nullptr})
    #define OBJ_VAL(object)         ((Value){ValueType::VAL_OBJ, static_cast<Obj*>(object)})

    static Value PrimitiveVal(ObjPrimitiveType* type)
    {
        Value value;
        value.type = ValueType::VAL_PRIMITIVE;
        value.as.primitive = type;
        return value;
    }
}