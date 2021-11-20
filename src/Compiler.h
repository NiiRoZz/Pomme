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

		void addFile(const std::string& filePath);
		void addString(const std::string& data);

		ObjFunction* compile(bool printTree = false);

	private:
		VirtualMachine& m_Vm;
		std::string compileString;
	};
}