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

	antlr3::generic_parse_return parser::program()
	{
		auto result = wrapped_call(get_specific_impl()->program);
		return {
			antlr3::common_token(result.start),
			antlr3::common_token(result.stop),
			antlr3::base_tree(result.tree)
		};
	}

	antlr3::generic_parse_return parser::statement()
	{
		auto result = wrapped_call(get_specific_impl()->statement);
		return {
			antlr3::common_token(result.start),
			antlr3::common_token(result.stop),
			antlr3::base_tree(result.tree)
		};
	}

	antlr3::generic_parse_return parser::expression()
	{
		auto result = wrapped_call(get_specific_impl()->expression);
		return {
			antlr3::common_token(result.start),
			antlr3::common_token(result.stop),
			antlr3::base_tree(result.tree)
		};
	}

	antlr3::generic_parse_return parser::atomic_expression()
	{
		auto result = wrapped_call(get_specific_impl()->atomic_expression);
		return {
			antlr3::common_token(result.start),
			antlr3::common_token(result.stop),
			antlr3::base_tree(result.tree)
		};
	}

	antlr3::generic_parse_return parser::declaration()
	{
		auto result = wrapped_call(get_specific_impl()->declaration);
		return {
			antlr3::common_token(result.start),
			antlr3::common_token(result.stop),
			antlr3::base_tree(result.tree)
		};
	}

	antlr3::generic_parse_return parser::assignment()
	{
		auto result = wrapped_call(get_specific_impl()->assignment);
		return {
			antlr3::common_token(result.start),
			antlr3::common_token(result.stop),
			antlr3::base_tree(result.tree)
		};
	}

	antlr3::generic_parse_return parser::unary_operation()
	{
		auto result = wrapped_call(get_specific_impl()->unary_operation);
		return {
			antlr3::common_token(result.start),
			antlr3::common_token(result.stop),
			antlr3::base_tree(result.tree)
		};
	}

	antlr3::generic_parse_return parser::binary_operation()
	{
		auto result = wrapped_call(get_specific_impl()->binary_operation);
		return {
			antlr3::common_token(result.start),
			antlr3::common_token(result.stop),
			antlr3::base_tree(result.tree)
		};
	}

	antlr3::generic_parse_return parser::literal()
	{
		auto result = wrapped_call(get_specific_impl()->literal);
		return {
			antlr3::common_token(result.start),
			antlr3::common_token(result.stop),
			antlr3::base_tree(result.tree)
		};
	}
}
