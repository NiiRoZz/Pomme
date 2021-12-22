#include "Chunk.h"
#include "VirtualMachine.h"

namespace Pomme
{
    void Chunk::writeChunk(uint8_t byte, int line)
    {
        code.push_back(byte);
        lines.push_back(line);

        count = code.size();
    }

    void Chunk::writeBeginChunk(uint8_t byte, int line)
    {
        code.insert(code.begin(), byte);
        lines.insert(lines.begin(), line);

        count = code.size();
    }

    void Chunk::writeBeginChunk(const Chunk& other)
    {
        code.insert(code.begin(), other.code.begin(), other.code.end());
        lines.insert(lines.begin(), other.lines.begin(), other.lines.end());
        constants.insert(constants.begin(), other.constants.begin(), other.constants.end());
        
        count = code.size();
    }

    int Chunk::addConstant(const Value& value)
    {
        constants.emplace_back(value);

        return constants.size() - 1;
    }

    void Chunk::clear()
    {
        code.clear();
        lines.clear();
        constants.clear();

        count = 0;
    }
}