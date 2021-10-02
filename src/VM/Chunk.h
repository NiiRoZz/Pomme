#pragma once

#include <cstdint>
#include <vector>

#include "Value.h"

namespace Pomme
{
    #define AS_OPCODE(code) static_cast<uint8_t>(code)

	enum class OpCode: uint8_t
    {
        OP_CONSTANT,
        OP_NEGATE,
        OP_ADD,
        OP_SUBTRACT,
        OP_MULTIPLY,
        OP_DIVIDE,
        OP_POP,
        OP_PRINT,
        OP_GET_GLOBAL,
        OP_SET_GLOBAL,
        OP_GET_LOCAL,
        OP_SET_LOCAL,
        OP_JUMP,
        OP_JUMP_IF_FALSE,
        OP_LOOP,
        OP_CALL,
        OP_RETURN,
    };

    class Chunk
    {
    public:
        void writeChunk(uint8_t byte, int line);
        int addConstant(Value value);

    public:
        std::vector<uint8_t> code;
        std::vector<Value> constants;

    private:
        std::vector<int> lines;
    };
}