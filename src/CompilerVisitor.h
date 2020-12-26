#pragma once

#include "PommeLexerVisitor.h"

namespace Pomme
{
	class VirtualMachine;

	class CompilerVisitor : public PommeLexerVisitor
	{
		VirtualMachine& m_Vm;

	public:
		CompilerVisitor(VirtualMachine &vm);

	public:

		// Inherited via TestLexerVisitor
		virtual void visit(const SimpleNode* node, void* data) override;
		virtual void visit(const ASTinput* node, void* data) override;
		virtual void visit(const ASTident* node, void* data) override;
		virtual void visit(const ASTinstrs* node, void* data) override;
		virtual void visit(const ASTinil* node, void* data) override;
		virtual void visit(const ASTvar* node, void* data) override;
		virtual void visit(const ASTomega* node, void* data) override;
		virtual void visit(const ASTvoidType* node, void* data) override;
	};
}