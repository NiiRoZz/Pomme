#include "Value.h"

namespace Pomme
{
    #ifndef NAN_BOXING
    Value::Value()
    : Value(ValueType::VAL_NULL)
    {
    }

    Value::Value(ValueType val)
    : type(val)
    {
    }

    Value::Value(Pointer val)
    : Value(ValueType::VAL_OBJ)
    {
        as.obj = val;
    }

    Value::Value(int32_t val)
    : Value(ValueType::VAL_PRIMITIVE)
    {
        as.primitive.type = PrimitiveType::INT;
        as.primitive.as.number = val;
    }

    Value::Value(double val)
    : Value(ValueType::VAL_PRIMITIVE)
    {
        as.primitive.type = PrimitiveType::FLOAT;
        as.primitive.as.numberFloat = val;
    }

    Value::Value(bool val)
    : Value(ValueType::VAL_PRIMITIVE)
    {
        as.primitive.type = PrimitiveType::BOOL;
        as.primitive.as.boolean = val;
    }
    #endif
}