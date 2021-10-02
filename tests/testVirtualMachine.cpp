#include "gtest/gtest.h"

#include "VM/VirtualMachine.h"
#include "VM/Chunk.h"

using namespace Pomme;

TEST(TEST_VM, BasicTest)
{
    ObjString functionName;
    ObjFunction function;
    function.obj.type = ObjType::OBJ_FUNCTION;
    function.arity = 0;
    function.name = &functionName;

    Chunk &chunk = function.chunk;

    int idxConstant = chunk.addConstant(NUMBER_VAL(10.0));
    chunk.writeChunk(static_cast<uint8_t>(OpCode::OP_CONSTANT));
    chunk.writeChunk(idxConstant);

    chunk.writeChunk(static_cast<uint8_t>(OpCode::OP_SET_GLOBAL));
    chunk.writeChunk(0x00);
    chunk.writeChunk(0x00);
    chunk.writeChunk(static_cast<uint8_t>(OpCode::OP_POP));

    chunk.writeChunk(static_cast<uint8_t>(OpCode::OP_GET_GLOBAL));
    chunk.writeChunk(0x00);
    chunk.writeChunk(0x00);

    chunk.writeChunk(static_cast<uint8_t>(OpCode::OP_RETURN));

    VirtualMachine vm;

    InterpretResult result = vm.interpret(&function);
    std::cout << "result of interpretation : " << static_cast<int>(result) << std::endl;
}