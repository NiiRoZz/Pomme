#pragma once

#include "VM/Object.h"
#include "TypeCheckerVisitor.h"

namespace Pomme
{
	class VirtualMachine;
	class SimpleNode;

	class TypeChecker
	{
	public:
        TypeChecker();
        TypeCheckerVisitor typeCheck(SimpleNode* tree);
	};
}