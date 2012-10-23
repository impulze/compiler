#include "antlr3_cc.h"
#include "boofar_lexer.h"
#include "boofar_parser.h"

#include <iostream>

namespace boofar
{
	class lexer
		: public antlr3::lexer_factory<boofar_lexer>
	{
	public:
		explicit lexer(antlr3::input_stream &);

	private:
		static ANTLR3_TOKEN_SOURCE *get_token_source(boofar_lexer *lexer);
	};

	class parser
		: public antlr3::parser_factory<boofar_parser>
	{
	public:
		explicit parser(antlr3::token_stream &);

		void parse();
	};
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		throw std::runtime_error("please specify a filename to parse");
	}

	antlr3::input_stream input_stream(argv[1]);
	boofar::lexer lexer(input_stream);
	antlr3::token_stream token_stream(lexer);

	std::vector<antlr3::common_token> tokens = token_stream.get_tokens();

	for (antlr3::common_token &token: tokens)
	{
		std::cout << "token: " << token.to_string() << std::endl;
	}

	boofar::parser parser(token_stream);

	parser.parse();

	return 0;
}

namespace boofar
{
	lexer::lexer(antlr3::input_stream &input_stream)
		: lexer_factory(boofar_lexerNew, get_token_source, input_stream)
	{
	}

	ANTLR3_TOKEN_SOURCE *lexer::get_token_source(boofar_lexer *lexer)
	{
		return TOKENSOURCE(lexer);
	}

	parser::parser(antlr3::token_stream &token_stream)
		: parser_factory(boofar_parserNew, token_stream)
	{
	}

	void parser::parse()
	{
		wrapped_call(get_specific_impl()->parse);
	}
}
