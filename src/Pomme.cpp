#include "Pomme.h"

#include "Compiler.h"
#include "VirtualMachine.h"

#include "PommeLexer.h"
#include "PommeLexerTokenManager.h"

#include <fstream>

using namespace Pomme;

int main()
{
	std::string filename = "input.pomme";
	std::ifstream stream;
	stream.open(filename);
	if (!stream.is_open())
	{
		std::cout << "failed to open " << filename << '\n\n';
	}

	JAVACC_STRING_TYPE s;
	while (!stream.eof()) {
		s += stream.get();
	}

	CharStream charStream(s.c_str(), s.size() - 1, 1, 1);

	PommeLexerTokenManager* scanner = new PommeLexerTokenManager(&charStream);
	PommeLexer lexer(scanner);

	PommeNode* tree = static_cast<PommeNode*>(lexer.input());
	tree->dump("");

	/*VirtualMachine vm;
	Compiler compiler(tree, vm);*/

	return 0;
}
