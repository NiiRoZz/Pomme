#include "Compiler.h"

#include "VM/VirtualMachine.h"
#include "CompilerVisitor.h"
#include "PommeLexerTokenManager.h"
#include "MyErrorHandler.h"
#include "PommeLexer.h"
#include "TypeChecker.h"

#include <iostream>

namespace Pomme
{
	Compiler::Compiler(VirtualMachine& vm)
	: m_Vm(vm)
	, compileString("")
	{
	}

	void Compiler::addFile(const std::string& filePath)
	{
		std::cerr << "Compiler::addFile not implemented yet" << std::endl;
		std::exit(1);
	}

	void Compiler::addString(const std::string& data)
	{
		compileString += data;
	}

	ObjFunction* Compiler::compile(bool printTree)
	{
		CharStream charStream(compileString.c_str(), compileString.size() - 1, 1, 1);
		MyErrorHandler *myErrorHandler = new MyErrorHandler();
		PommeLexerTokenManager scanner(&charStream);
		PommeLexer lexer(&scanner);
		lexer.setErrorHandler(myErrorHandler);
		PommeNode* tree = static_cast<PommeNode*>(lexer.input());

		if (printTree) tree->dump("");

		if (myErrorHandler->getErrorCount() > 0) return nullptr;

		TypeChecker typeChecker;
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
}