#pragma once

#include <vector>
#include <array>
#include <cstdint>
#include <type_traits>

#include "Object.h"
#include "Value.h"

namespace Pomme
{
    class ObjectMemory
    {
        static constexpr uint64_t GROW_CAPACITY_FACTOR = 2u;
        static constexpr std::size_t NUMBER_MAX_REF_COUNT = 64u;

        struct ObjectHeader
        {
            //Number of refCount
            uint8_t refCount;

            //Point to objects
            std::array<Pointer, NUMBER_MAX_REF_COUNT> refs;
        };

        static constexpr std::size_t HEADER_SIZE = sizeof(ObjectHeader);

    public:
        ObjectMemory(const std::size_t defaultCapacity);
        ~ObjectMemory();

    public:
        template<typename T, typename ...Args>
        Pointer alloc(Args&& ...args)
        {
            static_assert(std::is_base_of<Obj, T>::value, "You should allocate something that inherit from Obj class");

            Pointer pHeader = malloc(HEADER_SIZE + sizeof(T));
            Pointer p = pHeader + HEADER_SIZE;

            ObjectHeader* header = new (&m_Memory[pHeader]) ObjectHeader();
            header->refCount = 1u;

            T* obj = new (&m_Memory[p]) T(std::forward<Args>(args)...);
            obj->type = getObjType<T>();
            obj->pointer = p;

            return p;
        }

        template<typename T, typename ...Args>
        inline T* allocObject(Args&& ...args)
        {
            return get<T>(alloc<T>(std::forward<Args>(args)...));
        }

        Pointer malloc(std::size_t size);

        void free(Pointer p);
        void incRefCount(Pointer p);

        template<typename T>
        inline T* get(Pointer p) const
        {
            return reinterpret_cast<T*>(&m_Memory[p]);
        }

        inline ObjectHeader* getHeader(Pointer p) const
        {
            return reinterpret_cast<ObjectHeader*>(&m_Memory[p] - HEADER_SIZE);
        }

    private:
        uint8_t* m_Memory;
        uint64_t m_MemorySize;
        uint64_t m_MemoryCapacity;
    };
}