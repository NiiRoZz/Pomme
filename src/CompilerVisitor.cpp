#include "CompilerVisitor.h"
#include "CommonVisitorFunction.h"
#include "VM/VirtualMachine.h"
#include "VM/Chunk.h"

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
    , m_InNativeClass(false)
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

    void CompilerVisitor::visit(ASTPommeInput *node, void * data) 
    {
        line = node->getLineNumber();

        function = static_cast<ObjFunction*>(data);

        node->jjtChildrenAccept(this, nullptr);

        endCompiler();
    }

    void CompilerVisitor::visit(ASTPommeIdent *node, void * data) 
    {
        bool assign = (data == nullptr) ? false : *(bool*)data;

        if (node->m_Super) return;

        if (node->m_Attribute)
        {
            OpCode code = assign ? OpCode::OP_SET_PROPERTY : OpCode::OP_GET_PROPERTY;

            namedVariable("this", false);
            emitByte(AS_OPCODE(code));
            emit16Bits(node->m_IndexAttribute);
            return;
        }

        //Second, check if it's not a local var
        namedVariable(node->m_Identifier, assign);
    }

    void CompilerVisitor::visit(ASTPommeIdentOp *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeInt *node, void * data) 
    {
        emitInt(node->m_Value);
    }

    void CompilerVisitor::visit(ASTPommeFloat *node, void * data) 
    {
        emitFloat(node->m_Value);
    }

    void CompilerVisitor::visit(ASTPommeString *node, void * data) 
    {
        emitConstant(OBJ_PTR_VAL(m_Vm.copyString(node->m_Value.c_str() + 1, node->m_Value.length() - 2)->pointer));
    }

    void CompilerVisitor::visit(ASTPommeScopes *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
    }

    void CompilerVisitor::visit(ASTPommeScinil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeDecls *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
    }

    void CompilerVisitor::visit(ASTPommeDnil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeIdentFuncs *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeSnil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeVinil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeOnil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeDeclEnums *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeEnnil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeEnumAssign *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeEnumDefault *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeInstrs *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
    }

    void CompilerVisitor::visit(ASTPommeInil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeAssign *node, void * data) 
    {
        node->jjtChildAccept(1, this, data);

        bool value = true;
        node->jjtChildAccept(0, this, &value);
    }

    void CompilerVisitor::visit(ASTPommeAddEq *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeMinusEq *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeDivEq *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeMultEq *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeOrEq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        //emitByte(AS_OPCODE(OpCode::OP_OR_EQ));
    }

    void CompilerVisitor::visit(ASTPommeAndEq *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        //emitByte(AS_OPCODE(OpCode::OP_AND_EQ));
    }

    void CompilerVisitor::visit(ASTPommeShiftLEq *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeShiftREq *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeIncrPost *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeDecrPost *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeIncrPre *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeDecrPre *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeDelete *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTPommeReturn *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);
        emitByte(AS_OPCODE(OpCode::OP_RETURN));
    }

    void CompilerVisitor::visit(ASTPommeWhile *node, void * data) 
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

    void CompilerVisitor::visit(ASTPommeBreak *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeIf *node, void * data) 
    {
        //Condition
        node->jjtChildAccept(0, this, data);

        if (node->convert)
        {
            emitByte(AS_OPCODE(OpCode::OP_INVOKE));
            emit16Bits(node->index);
            emitByte(node->native);
            emit16Bits(0);
        }
        else if (node->testNull)
        {
            emitByte(AS_OPCODE(OpCode::OP_TEST_NOT_NULL));
        }

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

    void CompilerVisitor::visit(ASTPommePrint *node, void * data) 
    {
        node->jjtChildrenAccept(this, data);

        emitByte(AS_OPCODE(OpCode::OP_PRINT));
    }

    void CompilerVisitor::visit(ASTPommeSwitch *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeCases *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeDefault *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeSwinil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeListExp *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeExnil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeOmega *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeEnil *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeVoidType *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeAnd *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeOr *node, void * data) 
    {
    }

    void CompilerVisitor::visit(ASTPommeEQ *node, void * data) 
    {
        binaryOperator(node, node->index, node->native);
    }

    void CompilerVisitor::visit(ASTPommeNEQ *node, void * data) 
    {
        binaryOperator(node, node->index, node->native);
    }

    void CompilerVisitor::visit(ASTPommeGT *node, void * data) 
    {
        binaryOperator(node, node->index, node->native);
    }

    void CompilerVisitor::visit(ASTPommeGET *node, void * data) 
    {
        binaryOperator(node, node->index, node->native);
    }

    void CompilerVisitor::visit(ASTPommeLT *node, void * data) 
    {
        if (node->primitive)
        {
            node->jjtChildrenAccept(this, nullptr);
            emitByte(AS_OPCODE(node->opCode));
        }
        else
        {
            binaryOperator(node, node->index, node->native);
        }
    }

    void CompilerVisitor::visit(ASTPommeLET *node, void * data) 
    {
        binaryOperator(node, node->index, node->native);
    }

    void CompilerVisitor::visit(ASTPommeAdd *node, void * data) 
    {
        if (node->primitive)
        {
            node->jjtChildrenAccept(this, nullptr);
            emitByte(AS_OPCODE(node->opCode));
        }
        else
        {
            binaryOperator(node, node->index, node->native);
        }
    }

    void CompilerVisitor::visit(ASTPommeMinus *node, void * data) 
    {
        if (node->primitive)
        {
            node->jjtChildrenAccept(this, nullptr);
            emitByte(AS_OPCODE(node->opCode));
        }
        else
        {
            binaryOperator(node, node->index, node->native);
        }
    }

    void CompilerVisitor::visit(ASTPommeShiftR *node, void * data) 
    {
        binaryOperator(node, node->index, node->native);
    }

    void CompilerVisitor::visit(ASTPommeShiftL *node, void * data) 
    {
        binaryOperator(node, node->index, node->native);
    }

    void CompilerVisitor::visit(ASTPommeMult *node, void * data) 
    {
        binaryOperator(node, node->index, node->native);
    }

    void CompilerVisitor::visit(ASTPommeDiv *node, void * data) 
    {
        binaryOperator(node, node->index, node->native);
    }

    void CompilerVisitor::visit(ASTPommeModulo *node, void * data) 
    {
        binaryOperator(node, node->index, node->native);
    }

    void CompilerVisitor::visit(ASTPommeUnary *node, void * data) 
    {
        unaryOperator(node, node->index, node->native);
    }

    void CompilerVisitor::visit(ASTPommeNot *node, void * data) 
    {
        emitByte(AS_OPCODE(OpCode::OP_NOT));
    }

    void CompilerVisitor::visit(ASTPommeTilde *node, void * data) 
    {
        //emitByte(AS_OPCODE(OpCode::OP_TILDE));
    }

    void CompilerVisitor::visit(ASTPommeNew *node, void * data) 
    {
        uint16_t argCount = 0;

        std::string name = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;

        std::optional<std::size_t> global = m_Vm.getGlobal(name);

        if (!global.has_value())
        {
            assert(false);
        }

        emitBytes(AS_OPCODE(OpCode::OP_GET_GLOBAL), *global);

        ASTPommeListExp* exp = dynamic_cast<ASTPommeListExp*>(node->jjtGetChild(1));

        while (exp != nullptr)
        {
            argCount++;
            exp->jjtGetChild(0)->jjtAccept(this, nullptr);

            exp = dynamic_cast<ASTPommeListExp*>(exp->jjtGetChild(1));
        }

        emitByte(AS_OPCODE(OpCode::OP_NEW));
        emit16Bits(argCount);
        emitByte(node->foundConstructor);
        emit16Bits(node->index);
    }

    void CompilerVisitor::visit(ASTPommeTrue *node, void * data) 
    {
        emitBytes(AS_OPCODE(OpCode::OP_BOOL), 1u);
    }

    void CompilerVisitor::visit(ASTPommeFalse *node, void * data) 
    {
        emitBytes(AS_OPCODE(OpCode::OP_BOOL), 0u);
    }

    void CompilerVisitor::visit(ASTPommeNull *node, void * data) 
    {
        emitByte(AS_OPCODE(OpCode::OP_NULL));
    }

    void CompilerVisitor::visit(ASTPommeTypeDef *node, void * data)
    {
    }
    
    void CompilerVisitor::visit(ASTPommeClass *node, void * data)
    {
        const std::string& name = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;

        uint8_t nameConstant = makeConstant(OBJ_PTR_VAL(m_Vm.copyString(name.c_str(), name.length())->pointer));
        uint8_t global = m_Vm.addGlobal(name);

        emitBytes(AS_OPCODE(OpCode::OP_CLASS), nameConstant);
        emit64Bits(reinterpret_cast<uint8_t*>(&(node->nmbMethods)));
        emit64Bits(reinterpret_cast<uint8_t*>(&(node->nmbNativeMethods)));
        emit64Bits(reinterpret_cast<uint8_t*>(&(node->nmbStaticFields)));
        emit64Bits(reinterpret_cast<uint8_t*>(&(node->nmbFields)));
        
        emitBytes(AS_OPCODE(OpCode::OP_SET_GLOBAL), global);
        emitBytes(AS_OPCODE(OpCode::OP_GET_GLOBAL), global);

        m_InClass = true;
        m_InNativeClass = CommonVisitorFunction::isNativeType(name);

        node->jjtChildAccept(1, this, nullptr);

        m_InNativeClass = m_InClass = false;

        emitByte(AS_OPCODE(OpCode::OP_NR_POP));
    }

    void CompilerVisitor::visit(ASTPommeClassChild *node, void * data)
    {
        const std::string& name = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        const std::string& parentName = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1))->m_Identifier;

        m_SuperClass = parentName;

        uint8_t nameConstant = makeConstant(OBJ_PTR_VAL(m_Vm.copyString(name.c_str(), name.length())->pointer));
        std::optional<std::size_t> parentClass = m_Vm.getGlobal(parentName);
        assert(parentClass.has_value());

        uint8_t global = m_Vm.addGlobal(name);

        emitBytes(AS_OPCODE(OpCode::OP_CLASS), nameConstant);
        emit64Bits(reinterpret_cast<uint8_t*>(&(node->nmbMethods)));
        emit64Bits(reinterpret_cast<uint8_t*>(&(node->nmbNativeMethods)));
        emit64Bits(reinterpret_cast<uint8_t*>(&(node->nmbStaticFields)));
        emit64Bits(reinterpret_cast<uint8_t*>(&(node->nmbFields)));

        emitBytes(AS_OPCODE(OpCode::OP_SET_GLOBAL), global);

        emitBytes(AS_OPCODE(OpCode::OP_GET_GLOBAL), global);
        emitBytes(AS_OPCODE(OpCode::OP_GET_GLOBAL), *parentClass);
        emitByte(AS_OPCODE(OpCode::OP_INHERIT));

        m_InClass = true;

        node->jjtChildAccept(2, this, nullptr);

        m_InClass = false;

        emitByte(AS_OPCODE(OpCode::OP_NR_POP));
    }

    void CompilerVisitor::visit(ASTPommeModdedClass *node, void * data)
    {
        const std::string& name = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        const std::string& parentName = node->parentName;

        m_SuperClass = parentName;

        uint8_t nameConstant = makeConstant(OBJ_PTR_VAL(m_Vm.copyString(name.c_str(), name.length())->pointer));
        std::optional<std::size_t> parentClass = m_Vm.getGlobal(parentName);
        assert(parentClass.has_value());

        uint8_t global = m_Vm.addGlobal(name);

        emitBytes(AS_OPCODE(OpCode::OP_CLASS), nameConstant);
        emit64Bits(reinterpret_cast<uint8_t*>(&(node->nmbMethods)));
        emit64Bits(reinterpret_cast<uint8_t*>(&(node->nmbNativeMethods)));
        emit64Bits(reinterpret_cast<uint8_t*>(&(node->nmbStaticFields)));
        emit64Bits(reinterpret_cast<uint8_t*>(&(node->nmbFields)));

        emitBytes(AS_OPCODE(OpCode::OP_SET_GLOBAL), global);

        emitBytes(AS_OPCODE(OpCode::OP_GET_GLOBAL), global);
        emitBytes(AS_OPCODE(OpCode::OP_GET_GLOBAL), *parentClass);
        emitByte(AS_OPCODE(OpCode::OP_INHERIT));

        m_InClass = true;

        node->jjtChildAccept(1, this, nullptr);

        m_InClass = false;

        emitByte(AS_OPCODE(OpCode::OP_NR_POP));
    }

    void CompilerVisitor::visit(ASTPommeMethode *node, void * data)
    {
        auto* identFunc = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(2));
        auto* identOp = dynamic_cast<ASTPommeIdentOp*>(node->jjtGetChild(2));

        std::string ident = (identFunc != nullptr) ? identFunc->m_Identifier : identOp->m_Identifier;
        std::string identMethod = (identFunc != nullptr) ? identFunc->m_MethodIdentifier : identOp->m_MethodIdentifier;
        
        method(node, ident, identMethod, node->index, false);
    }

    void CompilerVisitor::visit(ASTPommeMethodeNative *node, void * data)
    {
        ASTPommeIdent* identFunc = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(3));
        ASTPommeIdentOp* identOp = dynamic_cast<ASTPommeIdentOp*>(node->jjtGetChild(3));
        //1: name
        std::string identMethod = (identFunc != nullptr) ? identFunc->m_MethodIdentifier : identOp->m_MethodIdentifier;

        uint8_t identConstant = makeConstant(OBJ_PTR_VAL(m_Vm.copyString(identMethod.c_str(), identMethod.length())->pointer));

        if (m_InNativeClass)
        {
            emitBytes(AS_OPCODE(OpCode::OP_CONSTANT), makeConstant(OBJ_PTR_VAL(m_Vm.newMethodPrimitiveNative()->pointer)));
        }
        else
        {
            emitBytes(AS_OPCODE(OpCode::OP_CONSTANT), makeConstant(OBJ_PTR_VAL(m_Vm.newMethodNative()->pointer)));
        }
        
        emitByte(AS_OPCODE(OpCode::OP_METHOD));
        emit16Bits(node->index);
        emitByte(identConstant);
        emitByte(true);
    }

    void CompilerVisitor::visit(ASTPommeStatic *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTPommePublic *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTPommePrivate *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTPommeProtected *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTPommeOverride *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTPommeEnum *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTPommeExtendsEnum *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTPommeModdedEnum *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTPommeGlobalFunction *node, void * data)
    {
        ASTPommeIdent* identFunc = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1));
        //1: name
        std::string name = identFunc->m_Identifier;
        std::string nameFunc = identFunc->m_MethodIdentifier;

        uint8_t global = m_Vm.addGlobal(nameFunc);

        ObjFunction* currentFunction = function;
        function = m_Vm.newFunction();

        function->name = m_Vm.copyString(name.c_str(), name.length());

        beginScope(); 

        addLocal("");

        beginScope(); 

        //2: parameters
        node->jjtChildAccept(2, this, data);

        //3: instrs
        node->jjtChildAccept(3, this, data);

        endScope();

        emitReturn();

        //Force end of begin scope without pop elements
        scopeDepth--;
        localCount--;

        ObjFunction* compiledFunction = function;
        function = currentFunction;

        emitBytes(AS_OPCODE(OpCode::OP_CONSTANT), makeConstant(OBJ_PTR_VAL(compiledFunction->pointer)));
        emitBytes(AS_OPCODE(OpCode::OP_SET_GLOBAL), global);
    }

    void CompilerVisitor::visit(ASTPommeGlobalFunctionNative *node, void * data)
    {
        ASTPommeIdent* identFunc = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1));
        //1: name
        std::string nameFunc = identFunc->m_MethodIdentifier;

        uint8_t global = m_Vm.addGlobal(nameFunc);

        emitBytes(AS_OPCODE(OpCode::OP_CONSTANT), makeConstant(OBJ_PTR_VAL(m_Vm.newGlobalNative()->pointer)));
        emitBytes(AS_OPCODE(OpCode::OP_SET_GLOBAL), global);
    }

    void CompilerVisitor::visit(ASTPommeCase *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTPommeVarDecls *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }

    void CompilerVisitor::visit(ASTPommeVariable *node, void * data)
    {
        //0: type
        std::string typeName = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;

        //1: name
        std::string name = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1))->m_Identifier;

        //2: expression value
        ASTPommeOmega* defaultValue = dynamic_cast<ASTPommeOmega*>(node->jjtGetChild(2));

        if (!m_InClass || (m_InClass && m_InMethod)) addLocal(name);

        if (m_InClass && !m_InMethod)
        {
            if (node->isStatic)
            {
                if (defaultValue != nullptr)
                {
                    emitDefaultValue(typeName);
                }
                else
                {
                    node->jjtGetChild(2)->jjtAccept(this, data);
                }
            }
            else
            {
                emitDefaultValue(typeName);
            }

            emitByte(AS_OPCODE(OpCode::OP_FIELD));
            emit16Bits(node->index);
            emitByte(makeConstant(OBJ_PTR_VAL(m_Vm.copyString(name.c_str(), name.length())->pointer)));
            emitByte(node->isStatic);
        }
        else
        {
            if (defaultValue != nullptr)
            {
                emitDefaultValue(typeName);
            }
            else
            {
                node->jjtGetChild(2)->jjtAccept(this, data);
            }
        }
    }

    void CompilerVisitor::visit(ASTPommeConstant *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTPommeHeaders *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }

    void CompilerVisitor::visit(ASTPommeConstHeader *node, void * data)
    {
        //1: name
        std::string name = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(2))->m_Identifier;
        addLocal(name);
        function->arity++;
    }

    void CompilerVisitor::visit(ASTPommeHeader *node, void * data)
    {
        //1: name
        std::string name = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1))->m_Identifier;
        addLocal(name);
        function->arity++;
    }

    void CompilerVisitor::visit(ASTPommeConstructor *node, void * data)
    {
        auto* name = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0));
        
        method(node, name->m_Identifier, name->m_MethodIdentifier, node->index, true);
    }

    void CompilerVisitor::visit(ASTPommeDestructor *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTPommeListAccess *node, void * data)
    {
        //We need to check for local variable or method
        node->jjtChildAccept(0, this, nullptr);
        
        accessProperty(nullptr, node->jjtGetChild(1), node->jjtGetChild(2), data);
    }

    void CompilerVisitor::visit(ASTPommeListAccessP *node, void * data)
    {
        accessProperty(node->jjtGetChild(0), node->jjtGetChild(1), node->jjtGetChild(2), data);
    }

    void CompilerVisitor::visit(ASTPommeAcnil *node, void * data)
    {
    }

    void CompilerVisitor::visit(ASTPommeAccessMethode *node, void * data)
    {
        //If we don't have GET_PROPERTY before, we are accessing method of global variable
        if (node->global)
        {
            namedVariable(node->name, false);
        }
        //Or we are in class and calling a method of this class without the "this" prefix
        else if (node->methodCall || node->superCall)
        {
            namedVariable("this", false);
        }

        uint16_t argCount = 0;

        ASTPommeListExp* exp = dynamic_cast<ASTPommeListExp*>(node->jjtGetChild(1));

        while (exp != nullptr)
        {
            argCount++;
            exp->jjtGetChild(0)->jjtAccept(this, nullptr);

            if (exp->convert)
            {
                if (exp->convertTo == "bool")
                {
                    emitByte(AS_OPCODE(OpCode::OP_INVOKE));
                    emit16Bits(exp->index);
                    emitByte(exp->native);
                    emit16Bits(0);
                }
            }

            exp = dynamic_cast<ASTPommeListExp*>(exp->jjtGetChild(1));
        }

        if (node->superCall)
        {
            std::optional<std::size_t> superIndex = m_Vm.getGlobal(m_SuperClass);
            assert(superIndex.has_value());
            emitBytes(AS_OPCODE(OpCode::OP_GET_GLOBAL), *superIndex);
            return;
        }

        if (node->methodCall)
        {
            emitByte(AS_OPCODE(OpCode::OP_INVOKE));
            emit16Bits(node->index);
            emitByte(node->native);
            emit16Bits(argCount);
            return;
        }
        
        if (node->global)
        {
            emitByte(AS_OPCODE(node->native ? OpCode::OP_CALL_NATIVE : OpCode::OP_CALL_GLOBAL));
            emit16Bits(argCount);
            return;
        }

        *static_cast<uint16_t*>(data) = argCount;
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

    void CompilerVisitor::emit32Bits(uint8_t* val)
    {
        for (int i = 0; i < 4; ++i)
        {
            emitByte(val[i]);
        }
    }

    void CompilerVisitor::emit64Bits(uint8_t* val)
    {
        for (int i = 0; i < 8; ++i)
        {
            emitByte(val[i]);
        }
    }

    void CompilerVisitor::emitInt(uint64_t val)
    {
        emitByte(AS_OPCODE(OpCode::OP_INT));
        emit32Bits(reinterpret_cast<uint8_t*>(&val));
    }

    void CompilerVisitor::emitFloat(double val)
    {
        emitByte(AS_OPCODE(OpCode::OP_FLOAT));
        emit64Bits(reinterpret_cast<uint8_t*>(&val));
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
        if (typeName == "int")
        {
            emitInt(0);
        }
        else if (typeName == "float")
        {
            emitFloat(0.0);
        }
        else if (typeName == "bool")
        {
            emitBytes(AS_OPCODE(OpCode::OP_BOOL), 0u);
        }
        else
        {
            emitByte(AS_OPCODE(OpCode::OP_NULL));
        }
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
        bool hasNext = dynamic_cast<ASTPommeAcnil*>(right) == nullptr;

        auto emitMethod = [&] (ASTPommeAccessMethode* method) { 
            if (method == nullptr) return false; 

            assert(!assign);

            uint16_t argCount;

            method->jjtAccept(this, &argCount);

            emitByte(AS_OPCODE(method->superCall ? OpCode::OP_INVOKE_SUPER : OpCode::OP_INVOKE));
            emit16Bits(method->index);
            emitByte(method->native);
            emit16Bits(argCount);

            return true;
        };

        auto emitIdent = [&] (ASTPommeIdent* ident, bool check, bool forceCheck) {
            if (ident == nullptr) return false; 

            OpCode code = OpCode::OP_GET_PROPERTY;
            if (forceCheck || (check && !hasNext)) code = assign ? OpCode::OP_SET_PROPERTY : OpCode::OP_GET_PROPERTY;

            emitByte(AS_OPCODE(code));
            emit16Bits(ident->m_IndexAttribute);

            return true;
        };

        if (left != nullptr)
        {
            emitMethod(dynamic_cast<ASTPommeAccessMethode*>(left)) || emitIdent(dynamic_cast<ASTPommeIdent*>(left), false, false);
        }

        if (middle != nullptr)
        {
            emitMethod(dynamic_cast<ASTPommeAccessMethode*>(middle)) || emitIdent(dynamic_cast<ASTPommeIdent*>(middle), true, false);
        }

        if (!hasNext || right == nullptr) return;

        //We continue through the list
        if (dynamic_cast<ASTPommeListAccessP*>(right) != nullptr)
        {
            right->jjtAccept(this, &assign);
            return;
        }

        emitMethod(dynamic_cast<ASTPommeAccessMethode*>(right)) || emitIdent(dynamic_cast<ASTPommeIdent*>(right), false, true);
    }

    void CompilerVisitor::method(SimpleNode *node, const std::string& ident, const std::string& methodIdent, uint16_t index, bool constructor)
    {
        uint8_t identConstant = makeConstant(OBJ_PTR_VAL(m_Vm.copyString(methodIdent.c_str(), methodIdent.length())->pointer));

        m_InMethod = true;

        ObjFunction* currentFunction = function;
        function = m_Vm.newFunction();

        function->name = m_Vm.copyString(ident.c_str(), ident.length());

        beginScope(); 

        addLocal("this");

        beginScope(); 

        //1 or 3: headers
        node->jjtChildAccept(constructor ? 1u : 3u, this, nullptr);

        //2 or 4: instrs
        node->jjtChildAccept(constructor ? 2u : 4u, this, nullptr);

        endScope();

        if (constructor)
        {
            emitBytes(AS_OPCODE(OpCode::OP_GET_LOCAL), 0u);
            emitByte(AS_OPCODE(OpCode::OP_RETURN));
        }
        else
        {
            emitReturn();
        }

        scopeDepth--;
        localCount--;

        ObjFunction* compiledFunction = function;
        function = currentFunction;

        emitBytes(AS_OPCODE(OpCode::OP_CONSTANT), makeConstant(OBJ_PTR_VAL(compiledFunction->pointer)));

        emitByte(AS_OPCODE(OpCode::OP_METHOD));
        emit16Bits(index);
        emitByte(identConstant);
        emitByte(false);

        m_InMethod = false;
    }

    void CompilerVisitor::unaryOperator(SimpleNode* node, uint16_t index, bool native)
    {
        node->jjtChildAccept(0, this, nullptr);

        emitByte(AS_OPCODE(OpCode::OP_INVOKE));
        emit16Bits(index);
        emitByte(native);
        emit16Bits(0);
    }

    void CompilerVisitor::binaryOperator(SimpleNode* node, uint16_t index, bool native)
    {
        node->jjtChildrenAccept(this, nullptr);

        emitByte(AS_OPCODE(OpCode::OP_INVOKE));
        emit16Bits(index);
        emitByte(native);
        emit16Bits(1);
    }

    int CompilerVisitor::addLocal(const std::string& name)
    {
        Local* local = &locals[localCount];
        local->name = name;
        local->depth = scopeDepth;

        return localCount++;
    }

    void CompilerVisitor::namedVariable(const std::string& name, bool assign)
    {
        OpCode op = (assign) ? OpCode::OP_SET_LOCAL : OpCode::OP_GET_LOCAL;

        //LOCALS
        for (int i = localCount - 1; i >= 0; i--)
        {
            if (name == locals[i].name)
            {
                emitBytes(AS_OPCODE(op), i);
                return;
            }
        }

        assert(!assign);

        //GLOBALS
        std::optional<std::size_t> idx = m_Vm.getGlobal(name);

        if (!idx.has_value())
        {
            assert(false);
        }

        emitBytes(AS_OPCODE(OpCode::OP_GET_GLOBAL), *idx);
    }

    void CompilerVisitor::visit(ASTPommeAccessTab *node, void * data)
    {
    }
}