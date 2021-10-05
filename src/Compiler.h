#pragma once

#include "VM/Object.h"

namespace Pomme
{
	class VirtualMachine;
	class SimpleNode;

	class Compiler
	{
	public:
		Compiler(VirtualMachine& vm);

		ObjFunction* compile(SimpleNode* tree);

	private:
		VirtualMachine& m_Vm;
	};
}