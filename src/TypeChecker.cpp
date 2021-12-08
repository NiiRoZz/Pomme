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

        if(visitorAutomate.dependanceGraph.hasLoop())
        {
            visitor.errors.emplace_back("File has circular dependance "+ visitorAutomate.dependanceGraph.loop);
            return visitor;
        }

        std::vector<int> state_order = visitorAutomate.dependanceGraph.topologicalSort();
        std::vector<Node*> class_to_define = visitorAutomate.dependanceGraph.getClassNode(&state_order);

        /*for(int path_number= 0; path_number < 3; path_number++)
        {
            for(auto it : class_to_define)
            {
                it->jjtAccept(&visitor,nullptr);
            }
            visitor.path_number++;
        }*/

        for(auto it : class_to_define)
        {
            it->jjtAccept(&visitor,nullptr);
        }

        visitor.path_number++;
        tree->jjtAccept(&visitor, nullptr);

        std::cout << visitor << std::endl;

        return visitor;
	}
}