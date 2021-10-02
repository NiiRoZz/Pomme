#include "Chunk.h"

namespace Pomme
{
    void Chunk::writeChunk(uint8_t byte)
    {
        code.push_back(byte);
    }

    int Chunk::addConstant(Value value)
    {
        constants.push_back(value);

        return constants.size() - 1;
    }
}