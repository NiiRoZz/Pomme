#include <iostream>
#include "TypeChecker.h"

#include "VM/VirtualMachine.h"
#include "CompilerVisitor.h"
#include "TypeCheckerVisitor.h"

namespace Pomme
{
	TypeChecker::TypeChecker(VirtualMachine& vm)
	: m_Vm(vm)
	{
	}

	std::vector<std::string> TypeChecker::typeCheck(SimpleNode* tree)
	{
		TypeCheckerVisitor visitor;
		tree->jjtAccept(&visitor, nullptr); // 1st pathing -> check double definition
        // tree->jjtAccept(&visitor, nullptr); // todo 2nd pathing -> name resolving

        std::cout << "------------------------" << std::endl;
        std::cout << "classMap :" << std::endl;
        for(const auto& it : visitor.classMap){
            std::cout << "class " << it.first << "{ \n" << it.second << "};"<< std::endl;
        }

        std::cout << "------------------------" << std::endl;
        std::cout << "globalFunctionsMap :" << std::endl;
        for(const auto& it : visitor.globalFunctionsMap){
            std::cout << "global function "<< it.second << std::endl;
        }

        return visitor.errors;
	}
}