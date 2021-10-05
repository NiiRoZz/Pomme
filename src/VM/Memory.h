#pragma once

#include <cstddef>
#include <cstdlib>

namespace Pomme
{
    #define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

    #define GROW_ARRAY(type, pointer, oldCount, newCount) \
        reinterpret_cast<type*>(reallocate(pointer, sizeof(type) * (oldCount), \
            sizeof(type) * (newCount)))

    #define ALLOCATE(type, count) \
            reinterpret_cast<type*>(reallocate(NULL, 0, sizeof(type) * (count)))
        
    #define ALLOCATE_OBJ(vm, type, objectType) \
        reinterpret_cast<type*>(vm->allocateObject(sizeof(type), objectType))

    #define FREE_ARRAY(type, pointer, oldCount) \
        reallocate(pointer, sizeof(type) * (oldCount), 0)

    #define FREE(type, pointer) reallocate(pointer, sizeof(type), 0)

    static void* reallocate(void* pointer, std::size_t oldSize, std::size_t newSize)
    {
        if (newSize == 0)
        {
            std::free(pointer);
            return nullptr;
        }

        void* result = std::realloc(pointer, newSize);
        if (result == nullptr) std::exit(1);
        
        return result;
    }
}