#include "Compiler.h"

#include "VM/VirtualMachine.h"
#include "CompilerVisitor.h"

namespace Pomme
{
	Compiler::Compiler(VirtualMachine& vm)
	: m_Vm(vm)
	{
	}

	ObjFunction* Compiler::compile(SimpleNode* tree)
	{
		ObjFunction* function = m_Vm.newFunction();

		CompilerVisitor visitor(m_Vm);
		tree->jjtAccept(&visitor, function);

		return function;
	}
}