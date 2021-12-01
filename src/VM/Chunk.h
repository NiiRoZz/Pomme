#pragma once

#include <cstdint>
#include <vector>
#include <iostream>

#include "Value.h"

namespace Pomme
{
    class VirtualMachine;

    #define AS_OPCODE(code) static_cast<uint8_t>(code)

	enum class OpCode: uint8_t
    {
        OP_CONSTANT,
        OP_NULL,
        OP_TEST_NOT_NULL,
        OP_POP,
        OP_PRINT,
        OP_GET_GLOBAL,
        OP_SET_GLOBAL,
        OP_GET_LOCAL,
        OP_SET_LOCAL,
        OP_GET_PROPERTY,
        OP_SET_PROPERTY,
        OP_INVOKE,
        OP_JUMP,
        OP_JUMP_IF_FALSE,
        OP_LOOP,
        OP_CALL_NATIVE,
        OP_CALL_GLOBAL,
        OP_RETURN,
        OP_FINISH,
        OP_INHERIT,
        OP_METHOD,
        OP_FIELD,
        OP_GET_SUPER,
        OP_NOT,
        OP_CLASS,
        OP_NEW,
        OP_INT,
        OP_FLOAT,
        OP_BOOL,
        OP_LT_INT_INT,
        OP_LT_INT_FLOAT,
        OP_LT_FLOAT_FLOAT,
        OP_LT_FLOAT_INT,
        OP_MINUS_INT_INT,
        OP_MINUS_INT_FLOAT,
        OP_MINUS_FLOAT_FLOAT,
        OP_MINUS_FLOAT_INT,
        OP_ADD_INT_INT,
        OP_ADD_INT_FLOAT,
        OP_ADD_FLOAT_FLOAT,
        OP_ADD_FLOAT_INT,
        COUNT,
    };

    class Chunk
    {
    public:
        void writeChunk(uint8_t byte, int line);
        int addConstant(const Value& value);

    public:
        uint64_t count;
        std::vector<uint8_t> code;
        std::vector<int> lines;

        std::vector<Value> constants;
    };
}