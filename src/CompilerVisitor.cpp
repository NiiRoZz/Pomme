#include "CompilerVisitor.h"
#include "VirtualMachine.h"

namespace Pomme
{
	CompilerVisitor::CompilerVisitor(VirtualMachine& vm)
	: m_Vm(vm)
	{
	}

	void CompilerVisitor::visit(const SimpleNode* node, void* data)
	{
	}

	void CompilerVisitor::visit(const ASTinput* node, void* data)
	{
	}

	void CompilerVisitor::visit(const ASTident* node, void* data)
	{
	}

	void CompilerVisitor::visit(const ASTinstrs* node, void* data)
	{
	}

	void CompilerVisitor::visit(const ASTinil* node, void* data)
	{
	}

	void CompilerVisitor::visit(const ASTvar* node, void* data)
	{
	}

	void CompilerVisitor::visit(const ASTomega* node, void* data)
	{
	}

	void CompilerVisitor::visit(const ASTvoidType* node, void* data)
	{
	}

}