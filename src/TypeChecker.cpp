#include <iostream>
#include "TypeChecker.h"

#include "VM/VirtualMachine.h"
#include "CompilerVisitor.h"
#include "TypeCheckerVisitor.h"

namespace Pomme
{
	TypeChecker::TypeChecker()
	{
	}

    TypeCheckerVisitor TypeChecker::typeCheck(SimpleNode* tree)
	{
		TypeCheckerVisitor visitor;
		tree->jjtAccept(&visitor, nullptr); // 1st pathing -> check double definition
        visitor.path_number++;
        //tree->jjtAccept(&visitor, nullptr); // todo 2nd pathing -> type resolving + child class

        std::cout << visitor << std::endl;

        return visitor;
	}
}