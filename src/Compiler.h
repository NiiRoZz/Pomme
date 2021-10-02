#pragma once

#include "VM/Object.h"

namespace Pomme
{
	class VirtualMachine;
	class SimpleNode;

	class Compiler
	{
		VirtualMachine& m_Vm;

	public:
		Compiler(SimpleNode* tree, VirtualMachine& vm, ObjFunction& function);
	};
}