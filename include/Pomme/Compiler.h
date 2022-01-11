#pragma once

#include "Object.h"
#include <string>

namespace Pomme
{
	class VirtualMachine;
	class SimpleNode;

	struct ErrorFile
	{
		ErrorFile(std::string fileName, std::size_t startLine, std::size_t endLine);

		std::string fileName;
		std::size_t startLine;
		std::size_t endLine;
	};

	class Compiler
	{
	public:
		Compiler(VirtualMachine& vm);

		void addFile(const std::string& filePath);
		void addString(const std::string& data);
		void addStdLibrary();

		ObjFunction* compile(bool printTree = false);

	private:
		void addCompileFile(const std::string& fileName, std::size_t sizeFile);

	private:
		VirtualMachine& m_Vm;
		std::string m_CompileString;

		std::vector<ErrorFile> m_CompileFiles;
	};
}