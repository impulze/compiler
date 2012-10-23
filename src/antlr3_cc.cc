#include "antlr3_cc.h"

namespace antlr3
{
	input_stream::input_stream(std::string const &filename)
	{
		ANTLR3_UINT8 const *uint8_filename = reinterpret_cast<ANTLR3_UINT8 const *>(filename.c_str());
		ANTLR3_INPUT_STREAM *input = antlr3FileStreamNew(const_cast<ANTLR3_UINT8 *>(uint8_filename), ANTLR3_ENC_UTF8);

		if (!input)
		{
			throw std::runtime_error("Unable to create input filename for ANTLR3");
		}

		shared_impl_.reset(input, releaser);
	}

	void input_stream::releaser(ANTLR3_INPUT_STREAM *input)
	{
		input->close(input);
	}

	std::string common_token::to_string()
	{
		ANTLR3_STRING *string = impl_->toString(impl_);
		char *chars = reinterpret_cast<char *>(string->chars);

		return std::string(chars, string->len);
	}

	token_stream::token_stream(lexer &lexer)
		: lexer_(lexer)
	{
		ANTLR3_TOKEN_SOURCE *token_source = lexer.get_token_source_implementation();
		ANTLR3_COMMON_TOKEN_STREAM *stream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, token_source);

		if (!stream)
		{
			throw std::runtime_error("Unable to create token stream for ANTLR3");
		}

		shared_impl_.reset(stream, releaser);
	}

	std::vector<common_token> token_stream::get_tokens()
	{
		std::vector<common_token> result;
		ANTLR3_VECTOR *vector = shared_impl_->getTokens(shared_impl_.get());

		for (ANTLR3_UINT32 i = 0; i < vector->count; i++)
		{
			ANTLR3_VECTOR_ELEMENT element = vector->elements[i];
			ANTLR3_COMMON_TOKEN *token = static_cast<ANTLR3_COMMON_TOKEN *>(element.element);
			result.push_back(common_token(token));
		}

		shared_impl_->reset(shared_impl_.get());

		return result;
	}

	void token_stream::releaser(ANTLR3_COMMON_TOKEN_STREAM *stream)
	{
		stream->free(stream);
	}
}