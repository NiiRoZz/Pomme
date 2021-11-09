
#include "CommonVisitorFunction.h"
#include "VM/VirtualMachine.h"
#include "VM/Chunk.h"
#include "VM/Memory.h"
#include "PommeLexerTree.h"

std::string CommonVisitorFunction::getParametersType(Pomme::Node *node) {
    auto* currHeaders = dynamic_cast<Pomme::ASTheaders*>(node);
    std::string parametersType;

    while (currHeaders != nullptr)
    {
        auto* currHeader = dynamic_cast<Pomme::ASTheader*>(currHeaders->jjtGetChild(0));
        auto* identHeader = dynamic_cast<Pomme::ASTident*>(currHeader->jjtGetChild(0));

        parametersType += identHeader->m_Identifier + HEADER_FUNC_SEPARATOR;

        currHeaders = dynamic_cast<Pomme::ASTheaders*>(currHeaders->jjtGetChild(1));
    }

    return parametersType;
}

std::string CommonVisitorFunction::getTypeName(Pomme::Node *node) {
    auto* identType = dynamic_cast<Pomme::ASTident*>(node);

    return ((identType != nullptr) ? identType->m_Identifier : "void");
}
