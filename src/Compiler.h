#pragma once


namespace Pomme
{
	class VirtualMachine;
	class SimpleNode;

	class Compiler
	{
		VirtualMachine& m_Vm;

	public:
		Compiler(SimpleNode* tree, VirtualMachine& vm);
	};
}