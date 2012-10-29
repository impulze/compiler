#include "boofar.h"

#include <iostream>

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

	antlr3::input_stream input_stream(filename);
	boofar::lexer lexer(input_stream);
	antlr3::token_stream token_stream(lexer);

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

		auto foo = parser.parse();
		auto tree = foo.tree;
		auto str = tree.to_string_tree();
		std::cout << str.to_std_string() << std::endl;
	}

	return 0;
}
