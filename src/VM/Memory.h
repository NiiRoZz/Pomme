#pragma once

#include <cstddef>
#include <cstdlib>

namespace Pomme
{
    #define ALLOCATE_OBJ(vm, type, objectType) \
        vm->allocateObject<type>(objectType)
}