#pragma once

#include "Object.h"
#include "TypeCheckerVisitor.h"

namespace Pomme
{
	class VirtualMachine;
	class SimpleNode;

	class TypeChecker
	{
	public:
        TypeChecker(const std::vector<ErrorFile>& errorFiles);
        TypeCheckerVisitor typeCheck(SimpleNode* tree);

	private:
		const std::vector<ErrorFile>& m_ErrorFiles;
	};
}