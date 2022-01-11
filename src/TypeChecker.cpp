#include <iostream>
#include "TypeChecker.h"

#include "VirtualMachine.h"
#include "CompilerVisitor.h"
#include "TypeCheckerVisitor.h"
#include "AutomateVisitor.h"

namespace Pomme
{
	TypeChecker::TypeChecker(const std::vector<ErrorFile>& errorFiles)
    : m_ErrorFiles(errorFiles)
	{
	}

    TypeCheckerVisitor TypeChecker::typeCheck(SimpleNode* tree)
	{
        AutomateVisitor visitorAutomate;
		TypeCheckerVisitor visitor(m_ErrorFiles);

        tree->jjtAccept(&visitorAutomate, nullptr);

        if(visitorAutomate.dependanceGraph.hasLoop())
        {
            visitor.errors.emplace_back("File has circular dependance "+ visitorAutomate.dependanceGraph.loop);
            return visitor;
        }

        std::vector<int> state_order = visitorAutomate.dependanceGraph.topologicalSort();
        std::vector<Node*> nodes = visitorAutomate.dependanceGraph.getClassNode(&state_order);

        /*for(int path_number= 0; path_number < 3; path_number++)
        {
            for(auto it : class_to_define)
            {
                it->jjtAccept(&visitor,nullptr);
            }
            visitor.path_number++;
        }*/

        for(auto* klass : nodes)
        {
            klass->jjtAccept(&visitor,nullptr);
        }

        if (visitor.errors.size() > 0)
        {
            return visitor;
        }

        visitor.path_number++;
        tree->jjtAccept(&visitor, nullptr);

        std::cout << visitor << std::endl;

        return visitor;
	}
}