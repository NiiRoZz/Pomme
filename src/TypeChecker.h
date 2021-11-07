#pragma once

#include "VM/Object.h"

namespace Pomme
{
	class VirtualMachine;
	class SimpleNode;

	class TypeChecker
	{
	public:
        TypeChecker(VirtualMachine& vm);

        std::vector<std::string> typeCheck(SimpleNode* tree);

	private:
		VirtualMachine& m_Vm;
	};
}