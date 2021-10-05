#include "Value.h"
#include "Memory.h"

namespace Pomme
{
    void ValueArray::write(const Value& value)
    {
        if (capacity < count + 1)
        {
            int oldCapacity = capacity;
            capacity = GROW_CAPACITY(oldCapacity);
            values = GROW_ARRAY(Value, values, oldCapacity, capacity);
        }

        values[count] = value;
        count++;
    }

    void initValueArray(ValueArray* array)
    {
        array->count = 0;
        array->capacity = 0;
        array->values = nullptr;
    }

    void freeValueArray(ValueArray* array)
    {
        FREE_ARRAY(Value, array->values, array->capacity);
        initValueArray(array);
    }
}