#pragma once

#include <cstdint>
#include <type_traits>
#include <typeinfo>

namespace Pomme
{
    struct Obj;

    enum class PrimitiveType: uint8_t
    {
        INT,
        FLOAT,
        BOOL,
        STRING,
        COUNT,
    };

    struct ObjPrimitive
    {
        PrimitiveType type;

        union
        {
            int64_t number;
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
        Value(Obj* val);
        Value(int64_t val);
        Value(double val);
        Value(bool val);

        inline bool isNull() const {return type == ValueType::VAL_NULL;}
        inline bool isObj() const {return type == ValueType::VAL_OBJ;}
        inline bool isPrimitive() const {return type == ValueType::VAL_PRIMITIVE;}

        inline ObjPrimitive& asPrimitive() {return as.primitive;}
        inline const ObjPrimitive& asPrimitive() const {return as.primitive;}
        Obj* asObj() const {return as.obj;}

    private:
        ValueType type;

        union
        {
            Obj* obj;
            ObjPrimitive primitive;
        } as;
    };
}