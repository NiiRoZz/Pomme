#include "Value.h"
#include "Memory.h"

namespace Pomme
{
    Value::Value()
    : Value(ValueType::VAL_NULL)
    {
    }

    Value::Value(ValueType val)
    : type(val)
    {
    }

    Value::Value(Obj* val)
    : Value(ValueType::VAL_OBJ)
    {
        as.obj = val;
    }

    Value::Value(int64_t val)
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
}