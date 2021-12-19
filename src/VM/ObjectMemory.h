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
            std::array<uint8_t*, NUMBER_MAX_REF_COUNT> refs;
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

            Pointer p = malloc(sizeof(T));

            T* obj = new (&m_Memory[p]) T(std::forward<Args>(args)...);
            obj->type = getObjType<T>();
            obj->pointer = p;

            return p;
        }

        template<typename T, typename ...Args>
        inline T* allocObject(Args&& ...args)
        {
            return reinterpret_cast<T*>(&m_Memory[alloc<T>(std::forward<Args>(args)...)]);
        }

        void free(Pointer p);
        void incRefCount(Pointer p);

        template<typename T>
        inline T* get(Pointer p)
        {
            static_assert(std::is_base_of<Obj, T>::value, "You should get something that inherit from Obj class");
            return reinterpret_cast<T*>(&m_Memory[p]);
        }

        template<typename T>
        inline const T* get(Pointer p) const
        {
            static_assert(std::is_base_of<Obj, T>::value, "You should get something that inherit from Obj class");
            return reinterpret_cast<const T*>(&m_Memory[p]);
        }

        inline ObjectHeader* getHeader(Pointer p) const
        {
            return reinterpret_cast<ObjectHeader*>(&m_Memory[p] - HEADER_SIZE);
        }

    private:
        Pointer malloc(std::size_t size);

    private:
        uint8_t* m_Memory;
        uint64_t m_MemorySize;
        uint64_t m_MemoryCapacity;
    };
}