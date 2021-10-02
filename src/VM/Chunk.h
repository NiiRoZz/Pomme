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
        OP_TRUE,
        OP_FALSE,
        OP_NULL,
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
        OP_MODULO,
        OP_SHIFTR,
        OP_SHIFTL,
        OP_EQ,
        OP_NEQ,
        OP_AND,
        OP_OR,
        OP_GT,
        OP_LT,
        OP_GET,
        OP_LET,
        OP_NOT,
        OP_TILDE,
        OP_ADD_EQ,
        OP_MULTIPLY_EQ,
        OP_SUBTRACT_EQ,
        OP_DIVIDE_EQ,
        OP_ASSIGN,
        OP_SHIFTL_EQ,
        OP_SHIFTR_EQ,
        OP_DECR_PRE,
        OP_DECR_POST,
        OP_INCR_PRE,
        OP_INCR_POST,
        OP_AND_EQ,
        OP_OR_EQ,
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