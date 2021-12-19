#include "ObjectMemory.h"
#include "Object.h"

#include <cstdlib>
#include <cstdint>

namespace Pomme
{
    ObjectMemory::ObjectMemory(const std::size_t defaultCapacity)
    : m_Memory(static_cast<uint8_t*>(std::malloc(defaultCapacity)))
    , m_MemorySize(1u)
    , m_MemoryCapacity(defaultCapacity)
    {
        std::memset(m_Memory, 0, m_MemoryCapacity);
    }

    ObjectMemory::~ObjectMemory()
    {
        std::free(m_Memory);
    }

    void ObjectMemory::free(Pointer p)
    {
        ObjectHeader* header = getHeader(p);
        header->refCount -= 1;

        if (header->refCount <= 0)
        {
            Obj* obj = get<Obj>(p);
            obj->~Obj();

            header->~ObjectHeader();

            //TODO: delete from memory
        }
    }

    Pointer ObjectMemory::malloc(std::size_t size)
    {
        const std::size_t newSize = m_MemorySize + HEADER_SIZE + size;

        if (newSize > m_MemoryCapacity)
        {
            std::size_t oldCapacity = m_MemoryCapacity;
            m_MemoryCapacity *= GROW_CAPACITY_FACTOR;
            m_Memory = static_cast<uint8_t*>(std::realloc(m_Memory, m_MemoryCapacity));
            std::memset(m_Memory + oldCapacity, 0, m_MemoryCapacity - oldCapacity);
        }

        Pointer p = m_MemorySize + HEADER_SIZE;

        ObjectHeader* header = new (&m_Memory[m_MemorySize]) ObjectHeader();
        header->refCount = 1u;

        m_MemorySize = newSize;

        return p;
    }
}