#include "Compiler.h"

#include "VM/VirtualMachine.h"
#include "CompilerVisitor.h"

namespace Pomme
{
	Compiler::Compiler(SimpleNode* tree, VirtualMachine& vm, ObjFunction& function)
	: m_Vm(vm)
	{
		CompilerVisitor visitor(vm, function);
		tree->jjtAccept(&visitor, nullptr);
	}
}