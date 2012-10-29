#include "boofar.h"

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

	boofar_parser_parse_return parser::parse()
	{
		return wrapped_call(get_specific_impl()->parse);
	}
}
