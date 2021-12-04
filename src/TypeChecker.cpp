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

        for(auto it : class_to_define)
        {
            std::cout << " Defining class : "<< dynamic_cast<ASTident*>(it->jjtGetChild(0))->m_Identifier << std::endl;
            it->jjtAccept(&visitor,nullptr);
        }

        // todo define globals headers
        // todo define functions headers

        //----
        // todo define globals instrs
        // todo define functions instrs

        visitor.path_number++;
        tree->jjtAccept(&visitor, nullptr);
        visitor.path_number++;
        tree->jjtAccept(&visitor, nullptr);

        std::cout << visitor << std::endl;

        return visitor;
	}
}