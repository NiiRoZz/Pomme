#include "CompilerVisitor.h"
#include "VM/VirtualMachine.h"
#include "VM/Chunk.h"

#include <iostream>

namespace Pomme
{
	CompilerVisitor::CompilerVisitor(VirtualMachine& vm, ObjFunction& function)
	: m_Vm(vm)
    , compilingChunk(&function.chunk)
	{

	}

    Chunk* CompilerVisitor::currentChunk()
    {
	  return compilingChunk;
	}

    void CompilerVisitor::emitBytes(uint8_t byte1, uint8_t byte2)
    {
        emitByte(byte1);
        emitByte(byte2);
    }

	void CompilerVisitor::emitByte(uint8_t byte)
    {
	    currentChunk()->writeChunk(byte, line);
	}

	void CompilerVisitor::endCompiler()
    {
		emitReturn();
	}

	void CompilerVisitor::emitReturn()
    {
		emitByte(AS_OPCODE(OpCode::OP_RETURN));
	}

    void CompilerVisitor::emitConstant(Value value)
    {
        emitBytes(AS_OPCODE(OpCode::OP_CONSTANT), makeConstant(value));
    }

    uint8_t CompilerVisitor::makeConstant(Value value)
    {
        int constant = currentChunk()->addConstant(value);
        if (constant > UINT8_MAX) {
            //error("Too many constants in one chunk.");
            return 0;
        }

        return (uint8_t)constant;
    }

    void CompilerVisitor::visit(const SimpleNode *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTinput *node, void * data) 
    {
        std::cout << "ASTinput " << node->jjtGetNumChildren() << std::endl;

        node->jjtChildrenAccept(this, data);

        endCompiler();
    }

    void CompilerVisitor::visit(const ASTident *node, void * data) 
    {
        std::cout << "ASTident : " << node->m_Identifier << std::endl;
    }

    void CompilerVisitor::visit(const ASTidentOp *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTpommeInt *node, void * data) 
    {
        std::cout << "ASTpommeInt : " << node->m_Value << std::endl;
    }

    void CompilerVisitor::visit(const ASTpommeFloat *node, void * data) 
    {
        std::cout << "ASTpommeFloat : " << node->m_Value << std::endl;
        emitConstant(NUMBER_VAL(node->m_Value));
    }

    void CompilerVisitor::visit(const ASTpommeString *node, void * data) 
    {
        std::cout << "ASTpommeString : " << node->m_Value << std::endl;
        ObjString* string = ALLOCATE_OBJ(ObjString, ObjType::OBJ_STRING);
        std::cout << "ASTpommeString.length() : " << node->m_Value.length() << std::endl;
        std::string str = node->m_Value.substr(1, node->m_Value.length() - 2);
        string->chars = str;
        std::cout << "ASTpommeString : " << node->m_Value << std::endl;

        emitConstant(OBJ_VAL(string));
    }

    void CompilerVisitor::visit(const ASTscopes *node, void * data) 
    {
        std::cout << "ASTscopes " << node->jjtGetNumChildren() << std::endl;

        node->jjtChildrenAccept(this, data);
    }

    void CompilerVisitor::visit(const ASTscinil *node, void * data) 
    {
        std::cout << "ASTscinil " << node->jjtGetNumChildren() << std::endl;
    }

    void CompilerVisitor::visit(const ASTdecls *node, void * data) 
    {
        std::cout << "ASTdecls " << node->jjtGetNumChildren() << std::endl;

        node->jjtChildrenAccept(this, data);
    }

    void CompilerVisitor::visit(const ASTdnil *node, void * data) 
    {
        std::cout << "ASTdnil " << node->jjtGetNumChildren() << std::endl;
    }

    void CompilerVisitor::visit(const ASTidentFuncs *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTsnil *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTvinil *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTonil *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTdeclenums *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTennil *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTenumassign *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTenumdefault *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTinstrs *node, void * data) 
    {
        std::cout << "ASTinstrs " << node->jjtGetNumChildren() << std::endl;

        node->jjtChildrenAccept(this, data);
    }

    void CompilerVisitor::visit(const ASTinil *node, void * data) 
    {
        std::cout << "ASTinil " << node->jjtGetNumChildren() << std::endl;
    }

    void CompilerVisitor::visit(const ASTassignement *node, void * data) 
    {
        emitByte(AS_OPCODE(OpCode::OP_ASSIGN));
    }

    void CompilerVisitor::visit(const ASTaddeq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_ADD_EQ));
    }

    void CompilerVisitor::visit(const ASTminuseq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_SUBTRACT_EQ));
    }

    void CompilerVisitor::visit(const ASTdiveq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_DIVIDE_EQ));
    }

    void CompilerVisitor::visit(const ASTmulteq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_MULTIPLY_EQ));
    }

    void CompilerVisitor::visit(const ASToreq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_OR_EQ));
    }

    void CompilerVisitor::visit(const ASTandeq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_AND_EQ));
    }

    void CompilerVisitor::visit(const ASTshiftleq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_SHIFTL_EQ));
    }

    void CompilerVisitor::visit(const ASTshiftreq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_SHIFTR_EQ));
    }

    void CompilerVisitor::visit(const ASTincrementPost *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_INCR_POST));
    }

    void CompilerVisitor::visit(const ASTdecrementPost *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_DECR_POST));
    }

    void CompilerVisitor::visit(const ASTincrementPre *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_INCR_PRE));
    }

    void CompilerVisitor::visit(const ASTdecrementPre *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_DECR_PRE));
    }

    void CompilerVisitor::visit(const ASTpommeReturn *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_RETURN));
    }

    void CompilerVisitor::visit(const ASTpommeWhile *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTpommeBreak *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTpommeIf *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTpommePrint *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);

        std::cout << "ASTpommePrint " << node->jjtGetNumChildren() << std::endl;

        emitByte(AS_OPCODE(OpCode::OP_PRINT));
    }

    void CompilerVisitor::visit(const ASTpommeSwitch *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTpommeCases *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTpommeDefault *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTswinil *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTlistexp *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTexnil *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTomega *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTenil *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTvoidType *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTpommeAnd *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_AND));
    }

    void CompilerVisitor::visit(const ASTpommeOr *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_OR));
    }

    void CompilerVisitor::visit(const ASTpommeEQ *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_EQ));
    }

    void CompilerVisitor::visit(const ASTpommeNEQ *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_NEQ));
    }

    void CompilerVisitor::visit(const ASTpommeGT *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_GT));
    }

    void CompilerVisitor::visit(const ASTpommeGET *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_GET));
    }

    void CompilerVisitor::visit(const ASTpommeLT *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_LT));
    }

    void CompilerVisitor::visit(const ASTpommeLET *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_LET));
    }

    void CompilerVisitor::visit(const ASTpommeAdd *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_ADD));
    }

    void CompilerVisitor::visit(const ASTpommeMinus *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_SUBTRACT));
    }

    void CompilerVisitor::visit(const ASTpommeShiftR *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_SHIFTR));
    }

    void CompilerVisitor::visit(const ASTpommeShiftL *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_SHIFTL));
    }

    void CompilerVisitor::visit(const ASTpommeMult *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_MULTIPLY));
    }

    void CompilerVisitor::visit(const ASTpommeDiv *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_DIVIDE));
    }

    void CompilerVisitor::visit(const ASTpommeModulo *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_MODULO));
    }

    void CompilerVisitor::visit(const ASTpommeUnary *node, void * data) 
    {
        emitByte(AS_OPCODE(OpCode::OP_NEGATE));
    }

    void CompilerVisitor::visit(const ASTpommeNot *node, void * data) 
    {
        emitByte(AS_OPCODE(OpCode::OP_NOT));
    }

    void CompilerVisitor::visit(const ASTpommeTilde *node, void * data) 
    {
        emitByte(AS_OPCODE(OpCode::OP_TILDE));
    }

    void CompilerVisitor::visit(const ASTpommeNew *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTpommeTrue *node, void * data) 
    {
        emitByte(AS_OPCODE(OpCode::OP_TRUE));
    }

    void CompilerVisitor::visit(const ASTpommeFalse *node, void * data) 
    {
        emitByte(AS_OPCODE(OpCode::OP_FALSE));
    }

    void CompilerVisitor::visit(const ASTpommeNull *node, void * data) 
    {
        emitByte(AS_OPCODE(OpCode::OP_NULL));
    }

    void CompilerVisitor::visit(const ASTaccessTab *node, void * data) 
    {

    }

    void CompilerVisitor::visit(const ASTpommeTypeDef *node, void * data)
    {
        
    }
    void CompilerVisitor::visit(const ASTpommeClass *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommeClassChild *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommeModdedClass *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommeMethode *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommeMethodeNative *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommeStatic *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommePublic *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommePrivate *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommeProtected *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommeOverride *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommeEnum *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommeExtendsEnum *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommeModdedEnum *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommeGlobalFunction *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }

    void CompilerVisitor::visit(const ASTpommeGlobalFunctionNative *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommeCase *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommeVariable *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommeConstant *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommeArray *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTheaders *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTheader *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTpommeDestructor *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTlistacces *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTacnil *node, void * data)
    {
        
    }

    void CompilerVisitor::visit(const ASTaccessMethode *node, void * data)
    {
        
    }
}