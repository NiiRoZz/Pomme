#pragma once

#include <cstdint>
#include <type_traits>
#include <typeinfo>
#include <cstring>
#include <cassert>

#include "Common.h"

namespace Pomme
{
    struct Obj;

    enum class PrimitiveType: uint8_t
    {
        INT,
        FLOAT,
        BOOL,
        COUNT,
    };

    using Pointer = uint32_t;

    #ifndef NAN_BOXING

    struct ObjPrimitive
    {
        PrimitiveType type;

        union
        {
            int32_t number;
            double numberFloat;
            bool boolean;
        } as;

        inline bool isType(PrimitiveType primitiveType) const {return type == primitiveType;}
    };

    enum class ValueType: uint8_t
    {
        VAL_NULL,
        VAL_OBJ,
        VAL_PRIMITIVE,
    };

    class Value
    {
    public:
        Value();
        Value(ValueType val);
        Value(Pointer val);
        Value(int32_t val);
        Value(double val);
        Value(bool val);

        bool isNull() const {return type == ValueType::VAL_NULL;}
        bool isObj() const {return type == ValueType::VAL_OBJ;}
        bool isPrimitive() const {return type == ValueType::VAL_PRIMITIVE;}

        ObjPrimitive& asPrimitive() {return as.primitive;}
        const ObjPrimitive& asPrimitive() const {return as.primitive;}
        Pointer asObj() const {return as.obj;}

    private:
        ValueType type;

        union
        {
            Pointer obj;
            ObjPrimitive primitive;
        } as;
    };

    #define IS_BOOL(value)          ((value).isPrimitive() && (value).asPrimitive().isType(PrimitiveType::BOOL))
    #define IS_NULL(value)          ((value).isNull())
    #define IS_INT(value)           ((value).isPrimitive() && (value).asPrimitive().isType(PrimitiveType::INT))
    #define IS_FLOAT(value)         ((value).isPrimitive() && (value).asPrimitive().isType(PrimitiveType::FLOAT))
    #define IS_OBJ(value)           ((value).isObj())

    #define NULL_VAL                (Value())
    #define OBJ_VAL(obj)            (Value(obj))
    #define BOOL_VAL(b)             (Value(b))
    #define FALSE_VAL               (Value(false))
    #define TRUE_VAL                (Value(true))
    #define INT_VAL(value)          (Value(value))
    #define FLOAT_VAL(num)          (Value(num))

    #define AS_OBJ(value)           ((value).asObj())
    #define AS_BOOL(value)          ((value).asPrimitive().as.boolean)
    #define AS_INT(value)           ((value).asPrimitive().as.number)
    #define AS_FLOAT(value)         ((value).asPrimitive().as.numberFloat)

    #else

    #define _MASK_SIGN              ((uint64_t)0x8000000000000000)
    #define _MASK_QNAN              ((uint64_t)0x7ffc000000000000)
    #define _MASK_INTEGER           (_MASK_QNAN | (uint64_t)0x0002000000000000)
    #define _MASK_OBJECT_PTR        (_MASK_QNAN | (uint64_t)0x8000000000000000)

    #define _PAYLOAD_INTEGER        ((uint64_t)0x00000000ffffffff)
    #define _PAYLOAD_OBJECT         ((uint64_t)0x0000ffffffffffff)

    #define TAG_NULL                1 // 01.
    #define TAG_FALSE               2 // 10.
    #define TAG_TRUE                3 // 11.

    using Value = uint64_t;

    #define IS_BOOL(value)          (((value) | 1) == TRUE_VAL)
    #define IS_NULL(value)          ((value) == NULL_VAL)
    #define IS_FLOAT(value)         (((value) & _MASK_QNAN) != _MASK_QNAN)
    #define IS_INT(value)           ((value & _MASK_INTEGER) == _MASK_INTEGER)
    #define IS_OBJ_PTR(value)       ((value & _MASK_OBJECT_PTR) == _MASK_OBJECT_PTR)

    #define BOOL_VAL(b)             ((b) ? TRUE_VAL : FALSE_VAL)
    #define FALSE_VAL               ((Value)(uint64_t)(_MASK_QNAN | TAG_FALSE))
    #define TRUE_VAL                ((Value)(uint64_t)(_MASK_QNAN | TAG_TRUE))
    #define NULL_VAL                ((Value)(uint64_t)(_MASK_QNAN | TAG_NULL))
    #define INT_VAL(value)          (_MASK_INTEGER | (uint32_t)(int32_t)(value))
    #define FLOAT_VAL(num)          doubleToValue(num)
    #define OBJ_PTR_VAL(obj)        (_MASK_OBJECT_PTR | (uint32_t)(int32_t)(obj))

    static inline Value doubleToValue(double num)
    {
        Value value;
        std::memcpy(&value, &num, sizeof(double));
        return value;
    }

    #define AS_BOOL(value)          ((value) == TRUE_VAL)
    #define AS_FLOAT(value)         doubleToNum(value)
    #define AS_INT(value)           ((int32_t)((value) & _PAYLOAD_INTEGER))
    #define AS_OBJ_PTR(value)       ((uint32_t)((value) & _PAYLOAD_INTEGER))
    #define AS_OBJ(vm, value)       ((vm).getObject<Obj>(AS_OBJ_PTR(value)))

    static inline double doubleToNum(Value value)
    {
        double num;
        std::memcpy(&num, &value, sizeof(Value));
        return num;
    }

    static inline PrimitiveType getPrimitiveTypeFromValue(Value value)
    {
        if (IS_INT(value))
        {
            return PrimitiveType::INT;
        }

        if (IS_FLOAT(value))
        {
            return PrimitiveType::FLOAT;
        }

        if (IS_BOOL(value))
        {
            return PrimitiveType::BOOL;
        }

        assert(false);
        return PrimitiveType::COUNT;
    }

    #endif
}