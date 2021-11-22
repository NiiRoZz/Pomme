#include "Chunk.h"
#include "Memory.h"
#include "VirtualMachine.h"

namespace Pomme
{
    void Chunk::writeChunk(uint8_t byte, int line)
    {
        code.emplace_back(byte);
        lines.emplace_back(line);
        count = code.size();
    }

    int Chunk::addConstant(const Value& value)
    {
        constants.push_back(value);

        return constants.size() - 1;
    }
}