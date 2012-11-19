#include "boofar_lexer.h"
#include "boofar_parser.h"
#include "boofar_traits.h"

#include <iostream>
#include <stdexcept>

static void usage()
{
	std::cerr << "parsing:       ./compiler <filename>\n"
	             "tokenize only: ./compiler --tokenize <filename>\n";

	throw std::runtime_error("illegal arguments");
}

int main(int argc, char *argv[])
{
	if (argc < 2 || argc > 3)
	{
		usage();
	}

	if (argc == 3)
	{
		if (std::string(argv[1]) != "--tokenize")
		{
			usage();
		}
	}

	char const *filename;

	if (argc == 3)
	{
		filename = argv[2];
	}
	else
	{
		filename = argv[1];
	}

	ANTLR_UINT8 const *antlr_filename = reinterpret_cast<ANTLR_UINT8 const *>(filename);
	boofar::traits::InputStreamType* input = new boofar::traits::InputStreamType(antlr_filename, ANTLR_ENC_8BIT);
	boofar::lexer *lexer = new boofar::lexer(input);

#if 0
	if (argc == 3)
	{
		std::vector<antlr3::common_token> tokens = token_stream.get_tokens();

		for (antlr3::common_token &token: tokens)
		{
			std::cout << "token: " << token.to_string() << std::endl;
		}
	}
	else
	{
		boofar::parser parser(token_stream);

		auto foo = parser.program();
		auto tree = foo.tree;
		auto str = tree.to_string_tree();
		std::cout << str.to_std_string() << std::endl;
	}
#endif

	return 0;
}
