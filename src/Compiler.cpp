#include "Compiler.h"

#include "VM/VirtualMachine.h"
#include "CompilerVisitor.h"

namespace Pomme
{
	Compiler::Compiler(SimpleNode* tree, VirtualMachine& vm)
	: m_Vm(vm)
	{
		/*CompilerVisitor visitor(vm);
		tree->jjtAccept(&visitor, nullptr);*/
	}
}