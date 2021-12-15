
#include "CommonVisitorFunction.h"
#include "VM/VirtualMachine.h"
#include "VM/Chunk.h"
#include "VM/Memory.h"
#include "PommeLexerTree.h"

#include <unordered_set>

namespace Pomme
{
    std::string CommonVisitorFunction::getParametersType(Pomme::Node *node)
    {
        auto* currHeaders = dynamic_cast<Pomme::ASTPommeHeaders*>(node);
        std::string parametersType;

        while (currHeaders != nullptr)
        {
            auto* currHeader = dynamic_cast<Pomme::ASTPommeHeader*>(currHeaders->jjtGetChild(0));
            auto* identHeader = dynamic_cast<Pomme::ASTPommeIdent*>(currHeader->jjtGetChild(0));

            parametersType += identHeader->m_Identifier + HEADER_FUNC_SEPARATOR;

            currHeaders = dynamic_cast<Pomme::ASTPommeHeaders*>(currHeaders->jjtGetChild(1));
        }

        return parametersType;
    }

    std::string CommonVisitorFunction::getTypeName(Pomme::Node *node)
    {
        auto* identType = dynamic_cast<Pomme::ASTPommeIdent*>(node);

        return ((identType != nullptr) ? identType->m_Identifier : "void");
    }

    bool CommonVisitorFunction::isNativeType(const std::string& name)
    {
        static std::unordered_set<std::string> nativeTypes = {"int", "float", "bool", "string"};
        return nativeTypes.count(name);
    }
}
