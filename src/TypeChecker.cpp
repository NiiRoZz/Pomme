#include <iostream>
#include "TypeChecker.h"

#include "VM/VirtualMachine.h"
#include "CompilerVisitor.h"
#include "TypeCheckerVisitor.h"
#include "AutomateVisitor.h"

namespace Pomme
{
	TypeChecker::TypeChecker()
	{
	}

    TypeCheckerVisitor TypeChecker::typeCheck(SimpleNode* tree)
	{
        AutomateVisitor visitorAutomate;

		TypeCheckerVisitor visitor;
        tree->jjtAccept(&visitorAutomate, nullptr); // class/method definition
		tree->jjtAccept(&visitor, nullptr); // class/method definition
        visitor.path_number++;
        tree->jjtAccept(&visitor, nullptr); // expression typing
        /*visitor.path_number++;
        tree->jjtAccept(&visitor, nullptr); // expression typing*/

        std::cout << visitor << std::endl;

        return visitor;
	}
}