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
	boofar::traits::InputStreamType input(antlr_filename, ANTLR_ENC_8BIT);
	boofar::lexer lexer(&input);
	boofar::traits::TokenStreamType token_stream(ANTLR_SIZE_HINT, lexer.get_tokSource());

	if (argc == 3)
	{
		token_stream.fillBuffer();
		auto tokens = token_stream.get_tokens();

		std::cout << tokens.size() << std::endl;

		for (boofar::traits::TokenStreamType::TokenType &token: tokens)
		{
			std::cout << "token: " << token.getText() << std::endl;
		}
	}
	else
	{
		boofar::parser parser(&token_stream);

		auto result = parser.declaration();
		std::cout << result << std::endl;
	}

	return 0;
}
