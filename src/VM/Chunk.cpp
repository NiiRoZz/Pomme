#include "Chunk.h"
#include "Memory.h"
#include "VirtualMachine.h"

namespace Pomme
{
    void Chunk::writeChunk(uint8_t byte, int line)
    {
        if (capacity < count + 1)
        {
            int oldCapacity = capacity;
            capacity = GROW_CAPACITY(oldCapacity);
            code = GROW_ARRAY(uint8_t, code, oldCapacity, capacity);
            lines = GROW_ARRAY(int, lines, oldCapacity, capacity);
        }

        code[count] = byte;
        lines[count] = line;
        count++;
    }

    int Chunk::addConstant(const Value& value)
    {
        constants.write(value);
        return constants.count - 1;
    }

    void initChunk(Chunk* chunk)
    {
        chunk->count = 0;
        chunk->capacity = 0;
        chunk->code = nullptr;
        chunk->lines = nullptr;
        initValueArray(&chunk->constants);
    }

    void freeChunk(Chunk* chunk)
    {
        FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
        FREE_ARRAY(int, chunk->lines, chunk->capacity);
        freeValueArray(&chunk->constants);
        initChunk(chunk);
    }
}