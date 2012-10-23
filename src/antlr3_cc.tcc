#include "antlr3_cc.h"

namespace antlr3
{
	template <class T>
	template <class CreateFunction, class TokenSourceFunction>
	lexer_factory<T>::lexer_factory(CreateFunction const &create_function,
	                                TokenSourceFunction const &token_source_function,
	                                input_stream &input_stream)
		: lexer(input_stream)
	{
		T *lexer = create_function(input_stream.get_implementation());

		if (!lexer)
		{
			throw std::runtime_error("Unable to create lexer for ANTLR3");
		}

		shared_impl_.reset(lexer, releaser);
		impl_ = lexer->pLexer;
		token_source_impl_ = token_source_function(lexer);
	}

	template <class T>
	void lexer_factory<T>::releaser(T *lexer)
	{
		lexer->free(lexer);
	}

	template <class T>
	template <class CreateFunction>
	parser_factory<T>::parser_factory(CreateFunction const &create_function,
	                                  token_stream &token_stream)
		: parser(token_stream)
	{
		T *parser = create_function(token_stream.get_implementation());

		if (!parser)
		{
			throw std::runtime_error("Unable to create parser for ANTLR3");
		}

		shared_impl_.reset(parser, releaser);
		impl_ = parser->pParser;
	}

	template <class T>
	void parser_factory<T>::releaser(T *parser)
	{
		parser->free(parser);
	}
}
