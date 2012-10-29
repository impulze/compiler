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

	antlr3::generic_parse_return parser::parse()
	{
		auto result = wrapped_call(get_specific_impl()->parse);
		return {
			antlr3::common_token(result.start),
			antlr3::common_token(result.stop),
			antlr3::base_tree(result.tree)
		};
	}

	antlr3::generic_parse_return parser::literals()
	{
		auto result = wrapped_call(get_specific_impl()->literals);
		return {
			antlr3::common_token(result.start),
			antlr3::common_token(result.stop),
			antlr3::base_tree(result.tree)
		};
	}

	antlr3::generic_parse_return parser::simple_assignment()
	{
		auto result = wrapped_call(get_specific_impl()->simple_assignment);
		return {
			antlr3::common_token(result.start),
			antlr3::common_token(result.stop),
			antlr3::base_tree(result.tree)
		};
	}
}
