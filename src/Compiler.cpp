#include "Compiler.h"

#include "VM/VirtualMachine.h"
#include "CompilerVisitor.h"
#include "PommeLexerTokenManager.h"
#include "MyErrorHandler.h"
#include "PommeLexer.h"
#include "TypeChecker.h"

#include <iostream>
#include <fstream>

namespace Pomme
{
	ErrorFile::ErrorFile(std::string fileName, std::size_t startLine, std::size_t endLine)
	: fileName(fileName)
	, startLine(startLine)
	, endLine(endLine)
	{
	}

	Compiler::Compiler(VirtualMachine& vm)
	: m_Vm(vm)
	, m_CompileString("")
	{
	}

	void Compiler::addFile(const std::string& filePath)
	{
		std::ifstream t(filePath);
		if (!t.good()) return;

		std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

		addCompileFile(filePath, std::count_if(filePath.begin(), filePath.end(), [](char i){return i == '\n';}));
		m_CompileString += str;
	}

	void Compiler::addString(const std::string& data)
	{
		static std::size_t stringNumber = 1u;

		addCompileFile("CustomString" + stringNumber++, std::count_if(data.begin(), data.end(), [](char i){return i == '\n';}));
		m_CompileString += data;
	}

	ObjFunction* Compiler::compile(bool printTree)
	{
		CharStream charStream(m_CompileString.c_str(), m_CompileString.size() - 1, 1, 1);
		MyErrorHandler *myErrorHandler = new MyErrorHandler();
		PommeLexerTokenManager scanner(&charStream);
		PommeLexer lexer(&scanner);
		lexer.setErrorHandler(myErrorHandler);
		PommeNode* tree = static_cast<PommeNode*>(lexer.input());

		if (printTree) tree->dump("");

		if (myErrorHandler->getErrorCount() > 0) return nullptr;

		TypeChecker typeChecker(m_CompileFiles);
		TypeCheckerVisitor typeCheckerVisitor = typeChecker.typeCheck(tree);

		if (typeCheckerVisitor.errors.size() > 0)
		{
			std::cerr << "TYPECHECKER ERROR :" << std::endl;
			for (const auto &error: typeCheckerVisitor.errors)
			{
				std::cerr << error << std::endl;
			}
			std::cerr << "END TYPECHECKER ERROR" << std::endl;
			return nullptr;
		}

		ObjFunction* function = m_Vm.newFunction();

		CompilerVisitor visitor(m_Vm);
		tree->jjtAccept(&visitor, function);

		return function;
	}

	void Compiler::addCompileFile(const std::string& fileName, std::size_t fileSize)
	{
		if (m_CompileFiles.size() > 0)
		{
			std::size_t startLine = m_CompileFiles[m_CompileFiles.size() - 1].endLine;
			m_CompileFiles.emplace_back(fileName, startLine, startLine + fileSize);
		}
		else
		{
			m_CompileFiles.emplace_back(fileName, 1u, fileSize);
		}
	}
}