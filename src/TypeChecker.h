#pragma once

#include "VM/Object.h"

namespace Pomme
{
	class VirtualMachine;
	class SimpleNode;

	class TypeChecker
	{
	public:
        TypeChecker();

        std::vector<std::string> typeCheck(SimpleNode* tree);
	};
}