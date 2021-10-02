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
    chunk.writeChunk(static_cast<uint8_t>(OpCode::OP_CONSTANT),1);
    chunk.writeChunk(idxConstant,1);

    chunk.writeChunk(static_cast<uint8_t>(OpCode::OP_SET_GLOBAL),1);
    chunk.writeChunk(0x00,1);
    chunk.writeChunk(0x00,1);
    chunk.writeChunk(static_cast<uint8_t>(OpCode::OP_POP),1);

    chunk.writeChunk(static_cast<uint8_t>(OpCode::OP_GET_GLOBAL),1);
    chunk.writeChunk(0x00,1);
    chunk.writeChunk(0x00,1);

    chunk.writeChunk(static_cast<uint8_t>(OpCode::OP_PRINT),1);
    chunk.writeChunk(static_cast<uint8_t>(OpCode::OP_RETURN),1);

    VirtualMachine vm;

    InterpretResult result = vm.interpret(&function);
    std::cout << "result of interpretation : " << static_cast<int>(result) << std::endl;
}