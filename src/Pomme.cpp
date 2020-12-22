// Pomme.cpp : Defines the entry point for the application.
//

#include "Pomme.h"

#include <antlr4-runtime.h>
#include "PommeLexer.h"
#include "PommeParser.h"

using namespace Pomme;

int main()
{
	//std::ifstream stream;
	//stream.open("input.scene");

	antlr4::ANTLRInputStream input("testtest");
	PommeLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);

	tokens.fill();
	for (auto token : tokens.getTokens()) {
		std::cout << token->toString() << std::endl;
	}

	PommeParser parser(&tokens);

	//parser.name()->accept();
	
	/*antlr4::tree::ParseTree *tree = parser.stored_definition();

	parser.main();

	Pomme::PommeParser::FileContext* tree = parser.file();*/

	return 0;
}
