#include "CompilerVisitor.h"
#include "CommonVisitorFunction.h"
#include "VM/VirtualMachine.h"
#include "VM/Chunk.h"
#include "VM/Memory.h"

#include <iostream>
#include <assert.h>

namespace Pomme
{
	CompilerVisitor::CompilerVisitor(VirtualMachine& vm)
	: m_Vm(vm)
    , function(nullptr)
    , localCount(0)
    , scopeDepth(0)
    , m_InClass(false)
    , m_InMethod(false)
	{
	}

    Chunk* CompilerVisitor::currentChunk()
    {
	  return &function->chunk;
	}

    void CompilerVisitor::visit(SimpleNode *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTinput *node, void * data) 
    {
        line = node->getLineNumber();

        function = static_cast<ObjFunction*>(data);

        node->jjtChildrenAccept(this, nullptr);

        endCompiler();
    }

    void CompilerVisitor::visit(ASTident *node, void * data) 
    {
        bool assign = (data == nullptr) ? false : *(bool*)data;

        if (node->m_Attribute)
        {
            OpCode code = assign ? OpCode::OP_SET_PROPERTY : OpCode::OP_GET_PROPERTY;

            namedVariable("this", false);
            emitByte(AS_OPCODE(code));
            emit16Bits(node->m_IndexAttribute);
        }
        else
        {
            //First check if it's a name of a class (for static method/property)
            if (!emitGetClass(node->m_Identifier))
            {
                //Second, check if it's not a local var or global method
                namedVariable(node->m_Identifier, assign);
            }
            else
            {
                assert(!assign);
            }
        }
    }

    void CompilerVisitor::visit(ASTidentOp *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTpommeInt *node, void * data) 
    {
        emitConstant(NUMBER_VAL((double) node->m_Value));
    }

    void CompilerVisitor::visit(ASTpommeFloat *node, void * data) 
    {
        emitConstant(NUMBER_VAL(node->m_Value));
    }

    void CompilerVisitor::visit(ASTpommeString *node, void * data) 
    {
        emitConstant(OBJ_VAL(m_Vm.copyString(node->m_Value.c_str() + 1, node->m_Value.length() - 2)));
    }

    void CompilerVisitor::visit(ASTscopes *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
    }

    void CompilerVisitor::visit(ASTscinil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTdecls *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
    }

    void CompilerVisitor::visit(ASTdnil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTidentFuncs *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTsnil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTvinil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTonil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTdeclenums *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTennil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTenumassign *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTenumdefault *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTinstrs *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
    }

    void CompilerVisitor::visit(ASTinil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTassignement *node, void * data) 
    {
        node->jjtChildAccept(1, this, data);

        bool value = true;
        node->jjtChildAccept(0, this, &value);
    }

    void CompilerVisitor::visit(ASTaddeq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_ADD_EQ));
    }

    void CompilerVisitor::visit(ASTminuseq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_SUBTRACT_EQ));
    }

    void CompilerVisitor::visit(ASTdiveq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_DIVIDE_EQ));
    }

    void CompilerVisitor::visit(ASTmulteq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_MULTIPLY_EQ));
    }

    void CompilerVisitor::visit(ASToreq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_OR_EQ));
    }

    void CompilerVisitor::visit(ASTandeq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_AND_EQ));
    }

    void CompilerVisitor::visit(ASTshiftleq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_SHIFTL_EQ));
    }

    void CompilerVisitor::visit(ASTshiftreq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_SHIFTR_EQ));
    }

    void CompilerVisitor::visit(ASTincrementPost *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_INCR_POST));
    }

    void CompilerVisitor::visit(ASTdecrementPost *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_DECR_POST));
    }

    void CompilerVisitor::visit(ASTincrementPre *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_INCR_PRE));
    }

    void CompilerVisitor::visit(ASTdecrementPre *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_DECR_PRE));
    }

    void CompilerVisitor::visit(ASTpommeReturn *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_RETURN));
    }

    void CompilerVisitor::visit(ASTpommeWhile *node, void * data) 
    {
        int loopStart = currentChunk()->count;

        //condition
        node->jjtChildAccept(0, this, data);

        int exitJump = emitJump(AS_OPCODE(OpCode::OP_JUMP_IF_FALSE));
        emitByte(AS_OPCODE(OpCode::OP_POP));

        //statement
        beginScope();
        node->jjtChildAccept(1, this, data);
        endScope();

        emitLoop(loopStart);
        
        patchJump(exitJump);

        emitByte(AS_OPCODE(OpCode::OP_POP));
    }

    void CompilerVisitor::visit(ASTpommeBreak *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTpommeIf *node, void * data) 
    {
        //Condition
        node->jjtChildAccept(0, this, data);

        int thenJump = emitJump(AS_OPCODE(OpCode::OP_JUMP_IF_FALSE));
        emitByte(AS_OPCODE(OpCode::OP_POP));

        //Statement
        beginScope();
        node->jjtChildAccept(1, this, data);
        endScope();

        int elseJump = emitJump(AS_OPCODE(OpCode::OP_JUMP));

        patchJump(thenJump);
        emitByte(AS_OPCODE(OpCode::OP_POP));

        beginScope();
        node->jjtChildAccept(2, this, data);
        endScope();

        patchJump(elseJump);
    }

    void CompilerVisitor::visit(ASTpommePrint *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);

        emitByte(AS_OPCODE(OpCode::OP_PRINT));
    }

    void CompilerVisitor::visit(ASTpommeSwitch *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTpommeCases *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTpommeDefault *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTswinil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTlistexp *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTexnil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTomega *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTenil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTvoidType *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTpommeAnd *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_AND));
    }

    void CompilerVisitor::visit(ASTpommeOr *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_OR));
    }

    void CompilerVisitor::visit(ASTpommeEQ *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_EQ));
    }

    void CompilerVisitor::visit(ASTpommeNEQ *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_NEQ));
    }

    void CompilerVisitor::visit(ASTpommeGT *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_GT));
    }

    void CompilerVisitor::visit(ASTpommeGET *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_GET));
    }

    void CompilerVisitor::visit(ASTpommeLT *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_LT));
    }

    void CompilerVisitor::visit(ASTpommeLET *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_LET));
    }

    void CompilerVisitor::visit(ASTpommeAdd *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_ADD));
    }

    void CompilerVisitor::visit(ASTpommeMinus *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_SUBTRACT));
    }

    void CompilerVisitor::visit(ASTpommeShiftR *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_SHIFTR));
    }

    void CompilerVisitor::visit(ASTpommeShiftL *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_SHIFTL));
    }

    void CompilerVisitor::visit(ASTpommeMult *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_MULTIPLY));
    }

    void CompilerVisitor::visit(ASTpommeDiv *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_DIVIDE));
    }

    void CompilerVisitor::visit(ASTpommeModulo *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_MODULO));
    }

    void CompilerVisitor::visit(ASTpommeUnary *node, void * data) 
    {
        emitByte(AS_OPCODE(OpCode::OP_NEGATE));
    }

    void CompilerVisitor::visit(ASTpommeNot *node, void * data) 
    {
        emitByte(AS_OPCODE(OpCode::OP_NOT));
    }

    void CompilerVisitor::visit(ASTpommeTilde *node, void * data) 
    {
        emitByte(AS_OPCODE(OpCode::OP_TILDE));
    }

    void CompilerVisitor::visit(ASTpommeNew *node, void * data) 
    {
        uint8_t argCount = 0;

        std::string name = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;

        std::optional<std::size_t> global = m_Vm.getGlobal(name);

        if (!global)
        {
            assert(false);
        }

        emitBytes(AS_OPCODE(OpCode::OP_GET_GLOBAL), *global);

        ASTlistexp* exp = dynamic_cast<ASTlistexp*>(node->jjtGetChild(1));

        while (exp != nullptr)
        {
            argCount++;
            exp->jjtGetChild(0)->jjtAccept(this, nullptr);

            exp = dynamic_cast<ASTlistexp*>(exp->jjtGetChild(1));
        }

        emitBytes(AS_OPCODE(OpCode::OP_NEW), argCount);
        emitByte(node->foundConstructor);
        emit16Bits(node->index);
    }

    void CompilerVisitor::visit(ASTpommeTrue *node, void * data) 
    {
        emitByte(AS_OPCODE(OpCode::OP_TRUE));
    }

    void CompilerVisitor::visit(ASTpommeFalse *node, void * data) 
    {
        emitByte(AS_OPCODE(OpCode::OP_FALSE));
    }

    void CompilerVisitor::visit(ASTpommeNull *node, void * data) 
    {
        emitByte(AS_OPCODE(OpCode::OP_NULL));
    }

    void CompilerVisitor::visit(ASTpommeTypeDef *node, void * data)
    {
    }
    
    void CompilerVisitor::visit(ASTpommeClass *node, void * data)
    {
        const std::string& name = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;

        uint8_t nameConstant = makeConstant(OBJ_VAL(m_Vm.copyString(name.c_str(), name.length())));
        uint8_t global = m_Vm.addGlobal(name);

        emitBytes(AS_OPCODE(OpCode::OP_CLASS), nameConstant);
        emitBytes(AS_OPCODE(OpCode::OP_SET_GLOBAL), global);
        emitBytes(AS_OPCODE(OpCode::OP_GET_GLOBAL), global);

        m_InClass = true;

        node->jjtChildAccept(1, this, nullptr);

        m_InClass = false;

        emitByte(AS_OPCODE(OpCode::OP_POP));
    }

    void CompilerVisitor::visit(ASTpommeClassChild *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTpommeModdedClass *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTpommeMethode *node, void * data)
    {
        auto* name = dynamic_cast<ASTident*>(node->jjtGetChild(2));
        
        method(node, name, node->index, false);
    }

    void CompilerVisitor::visit(ASTpommeMethodeNative *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTpommeStatic *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTpommePublic *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTpommePrivate *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTpommeProtected *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTpommeOverride *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTpommeEnum *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTpommeExtendsEnum *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTpommeModdedEnum *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTpommeGlobalFunction *node, void * data)
    {
        ASTident* identFunc = dynamic_cast<ASTident*>(node->jjtGetChild(1));
        //1: name
        std::string name = identFunc->m_Identifier;
        std::string nameFunc = identFunc->m_MethodIdentifier;

        uint8_t global = m_Vm.addGlobal(nameFunc);

        ObjFunction* currentFunction = function;
        function = m_Vm.newFunction();

        function->name = m_Vm.copyString(name.c_str(), name.length());

        beginScope(); 

        addLocal("");

        //2: parameters
        node->jjtChildAccept(2, this, data);

        //3: instrs
        node->jjtChildAccept(3, this, data);

        emitReturn();

        endScope();

        ObjFunction* compiledFunction = function;
        function = currentFunction;

        emitBytes(AS_OPCODE(OpCode::OP_CONSTANT), makeConstant(OBJ_VAL(compiledFunction)));
        emitBytes(AS_OPCODE(OpCode::OP_SET_GLOBAL), global);
    }

    void CompilerVisitor::visit(ASTpommeGlobalFunctionNative *node, void * data)
    {
        ASTident* identFunc = dynamic_cast<ASTident*>(node->jjtGetChild(1));
        //1: name
        std::string name = identFunc->m_Identifier;
        std::string nameFunc = identFunc->m_MethodIdentifier;

        uint8_t global = m_Vm.addGlobal(nameFunc);

        emitBytes(AS_OPCODE(OpCode::OP_CONSTANT), makeConstant(OBJ_VAL(m_Vm.newGlobalNative())));
        emitBytes(AS_OPCODE(OpCode::OP_SET_GLOBAL), global);
    }

    void CompilerVisitor::visit(ASTpommeCase *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTvarDecls *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }

    void CompilerVisitor::visit(ASTpommeVariable *node, void * data)
    {
        //0: type
        std::string typeName = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;

        //1: name
        std::string name = dynamic_cast<ASTident*>(node->jjtGetChild(1))->m_Identifier;

        //2: expression value
        ASTomega* defaultValue = dynamic_cast<ASTomega*>(node->jjtGetChild(2));

        if (!m_InClass || (m_InClass && m_InMethod)) addLocal(name);

        if (defaultValue != nullptr)
        {
            emitDefaultValue(typeName);
        }
        else
        {
            node->jjtGetChild(2)->jjtAccept(this, data);
        }

        if (m_InClass && !m_InMethod)
        {
            emitByte(AS_OPCODE(OpCode::OP_FIELD));
            emit16Bits(node->index);
            emitByte(makeConstant(OBJ_VAL(m_Vm.copyString(name.c_str(), name.length()))));
            emitByte(node->isStatic);
        }
    }

    void CompilerVisitor::visit(ASTpommeConstant *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTheaders *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }

    void CompilerVisitor::visit(ASTheader *node, void * data)
    {
        //1: name
        std::string name = dynamic_cast<ASTident*>(node->jjtGetChild(1))->m_Identifier;
        addLocal(name);
        function->arity++;
    }

    void CompilerVisitor::visit(ASTpommeConstructor *node, void * data)
    {
        auto* name = dynamic_cast<ASTident*>(node->jjtGetChild(0));
        
        method(node, name, node->index, true);
    }

    void CompilerVisitor::visit(ASTpommeDestructor *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTlistacces *node, void * data)
    {
        //We need to check for local variable or method
        node->jjtChildAccept(0, this, nullptr);
        
        accessProperty(nullptr, node->jjtGetChild(1), node->jjtGetChild(2), data);
    }

    void CompilerVisitor::visit(ASTlistaccesP *node, void * data)
    {
        accessProperty(node->jjtGetChild(0), node->jjtGetChild(1), node->jjtGetChild(2), data);
    }

    void CompilerVisitor::visit(ASTacnil *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTaccessMethode *node, void * data)
    {
        //If we don't have GET_PROPERTY before, we are accessing method of current class or global variable
        if (node->global)
        {
            namedVariable(node->name, false);
        }

        uint8_t argCount = 0;

        ASTlistexp* exp = dynamic_cast<ASTlistexp*>(node->jjtGetChild(1));

        while (exp != nullptr)
        {
            argCount++;
            exp->jjtGetChild(0)->jjtAccept(this, nullptr);

            exp = dynamic_cast<ASTlistexp*>(exp->jjtGetChild(1));
        }

        emitBytes(AS_OPCODE(OpCode::OP_CALL), argCount);
    }

	void CompilerVisitor::emitByte(uint8_t byte)
    {
	    currentChunk()->writeChunk(byte, line);
	}

    void CompilerVisitor::emitBytes(uint8_t byte1, uint8_t byte2)
    {
        emitByte(byte1);
        emitByte(byte2);
    }

    void CompilerVisitor::emit16Bits(uint16_t val)
    {
        emitByte((val >> 8) & 0xff);
        emitByte(val & 0xff);
    }

	void CompilerVisitor::endCompiler()
    {
		emitReturn();
	}

	void CompilerVisitor::emitReturn()
    {
        emitByte(AS_OPCODE(OpCode::OP_NULL));
		emitByte(AS_OPCODE(OpCode::OP_RETURN));
	}

    int CompilerVisitor::emitJump(uint8_t instruction)
    {
        emitByte(instruction);
        emitByte(0xff);
        emitByte(0xff);
        return currentChunk()->count - 2;
    }

	void CompilerVisitor::patchJump(int offset)
    {
        // -2 to adjust for the bytecode for the jump offset itself.
        int jump = currentChunk()->count - offset - 2;

        if (jump > UINT16_MAX)
        {
            //error("Too much code to jump over.");
        }

        currentChunk()->code[offset] = (jump >> 8) & 0xff;
        currentChunk()->code[offset + 1] = jump & 0xff;
    }

    void CompilerVisitor::emitLoop(int loopStart)
    {
        emitByte(AS_OPCODE(OpCode::OP_LOOP));

        int offset = currentChunk()->count - loopStart + 2;
        //if (offset > UINT16_MAX) error("Loop body too large.");

        emit16Bits((uint16_t) offset);
    }

    void CompilerVisitor::emitDefaultValue(const std::string& typeName)
    {
        emitByte(AS_OPCODE(OpCode::OP_NULL));
    }

    bool CompilerVisitor::emitGetClass(const std::string& name)
    {
        std::optional<std::size_t> idx = m_Vm.getGlobal(name);

        if (!idx.has_value())
        {
            return false;
        }

        emitBytes(AS_OPCODE(OpCode::OP_GET_GLOBAL), *idx);

        return true;
    }

    void CompilerVisitor::emitConstant(const Value& value)
    {
        emitBytes(AS_OPCODE(OpCode::OP_CONSTANT), makeConstant(value));
    }

    uint8_t CompilerVisitor::makeConstant(const Value& value)
    {
        int constant = currentChunk()->addConstant(value);
        if (constant > UINT16_MAX)
        {
            //error("Too many constants in one chunk.");
            return 0;
        }

        return (uint8_t)constant;
    }

    void CompilerVisitor::beginScope()
    {
        scopeDepth++;
    }

    void CompilerVisitor::endScope()
    {
        scopeDepth--;

        while (localCount > 0 && locals[localCount - 1].depth > scopeDepth)
        {
            emitByte(AS_OPCODE(OpCode::OP_POP));
            localCount--;
        }
    }

    void CompilerVisitor::accessProperty(Node* left, Node* middle, Node* right, void * data)
    {
        bool assign = (data == nullptr) ? false : *(bool*)data;
        bool hasNext = dynamic_cast<ASTacnil*>(right) == nullptr;

        auto emitMethod = [&] (ASTaccessMethode* method) { 
            if (method == nullptr) return false; 

            assert(!assign);

            emitByte(AS_OPCODE(OpCode::OP_GET_METHOD));
            emit16Bits(method->index);

            method->jjtAccept(this, &assign);

            return true;
        };

        auto emitIdent = [&] (ASTident* ident, bool check, bool forceCheck) {
            if (ident == nullptr) return false; 

            OpCode code = OpCode::OP_GET_PROPERTY;
            if (forceCheck || (check && !hasNext)) code = assign ? OpCode::OP_SET_PROPERTY : OpCode::OP_GET_PROPERTY;

            emitByte(AS_OPCODE(code));
            emit16Bits(ident->m_IndexAttribute);

            return true;
        };

        if (left != nullptr)
        {
            emitMethod(dynamic_cast<ASTaccessMethode*>(left)) || emitIdent(dynamic_cast<ASTident*>(left), false, false);
        }

        emitMethod(dynamic_cast<ASTaccessMethode*>(middle)) || emitIdent(dynamic_cast<ASTident*>(middle), true, false);

        if (!hasNext) return;

        //We continue through the list
        if (dynamic_cast<ASTlistaccesP*>(right) != nullptr)
        {
            right->jjtAccept(this, &assign);
            return;
        }

        emitMethod(dynamic_cast<ASTaccessMethode*>(right)) || emitIdent(dynamic_cast<ASTident*>(right), false, true);
    }

    void CompilerVisitor::method(SimpleNode *node, ASTident *name, uint16_t index, bool constructor)
    {
        std::string& ident = name->m_MethodIdentifier;
        uint8_t identConstant = makeConstant(OBJ_VAL(m_Vm.copyString(ident.c_str(), ident.length())));

        m_InMethod = true;

        ObjFunction* currentFunction = function;
        function = m_Vm.newFunction();

        function->name = m_Vm.copyString(name->m_Identifier.c_str(), name->m_Identifier.length());

        beginScope(); 

        addLocal("this");

        //1 or 3: headers
        node->jjtChildAccept(constructor ? 1u : 3u, this, nullptr);

        //2 or 4: instrs
        node->jjtChildAccept(constructor ? 2u : 4u, this, nullptr);

        if (constructor)
        {
            emitBytes(AS_OPCODE(OpCode::OP_GET_LOCAL), 0);
            emitByte(AS_OPCODE(OpCode::OP_RETURN));
        }
        else
        {
            emitReturn();
        }

        endScope();

        ObjFunction* compiledFunction = function;
        function = currentFunction;

        emitBytes(AS_OPCODE(OpCode::OP_CONSTANT), makeConstant(OBJ_VAL(compiledFunction)));

        emitByte(AS_OPCODE(OpCode::OP_METHOD));
        emit16Bits(index);
        emitByte(identConstant);

        m_InMethod = false;
    }

    int CompilerVisitor::addLocal(const std::string& name)
    {
        int idx = localCount;

        Local* local = &locals[localCount++];
        local->name = name;
        local->depth = scopeDepth;

        return idx;
    }

    void CompilerVisitor::namedVariable(const std::string& name, bool assign)
    {
        OpCode op = OpCode::OP_GET_LOCAL;

        if (assign)
        {
            op = OpCode::OP_SET_LOCAL;
        }

        //LOCALS
        for (uint8_t i = localCount - 1; i >= 0; i--)
        {
            Local& local = locals[i];

            if (local.depth != -1 && local.depth < scopeDepth)
            {
                break; 
            }

            if (name == local.name)
            {
                emitBytes(AS_OPCODE(op), i);
                return;
            }
        }

        //GLOBALS
        op = (assign) ? OpCode::OP_SET_GLOBAL : OpCode::OP_GET_GLOBAL;

        std::optional<std::size_t> idx = m_Vm.getGlobal(name);

        if (!idx.has_value())
        {
            assert(false);
        }

        emitBytes(AS_OPCODE(op), *idx);
    }
}