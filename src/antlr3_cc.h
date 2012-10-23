#ifndef ANTLR3_CC_H_INCLUDED
#define ANTLR3_CC_H_INCLUDED

#include <antlr3.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace antlr3
{
	class input_stream
	{
	public:
		explicit input_stream(std::string const &filename);

		/* you're on your own using this, don't expect anything */
		ANTLR3_INPUT_STREAM *get_implementation()
		{
			return shared_impl_.get();
		}

	private:
		static void releaser(ANTLR3_INPUT_STREAM *);

		std::shared_ptr<ANTLR3_INPUT_STREAM> shared_impl_;
	};

	class lexer
	{
	public:
		explicit lexer(input_stream &input_stream)
			: input_stream_(input_stream)
		{
		}

		virtual ~lexer()
		{
		}

		input_stream &get_input_stream()
		{
			return input_stream_;
		}

		input_stream const &get_input_stream() const
		{
			return input_stream_;
		}

		/* you're on your own using this, don't expect anything */
		ANTLR3_LEXER *get_implementation()
		{
			return impl_;
		}

		ANTLR3_TOKEN_SOURCE *get_token_source_implementation()
		{
			return token_source_impl_;
		}

	protected:
		/* those have to be set by the deriving class */
		ANTLR3_LEXER *impl_;
		ANTLR3_TOKEN_SOURCE *token_source_impl_;

	private:
		input_stream input_stream_;
	};

	template <class T>
	class lexer_factory
		: public lexer
	{
	public:
		template <class CreateFunction, class TokenSourceFunction>
		lexer_factory(CreateFunction const &create_function,
		              TokenSourceFunction const &token_source_function,
		              input_stream &input_stream);

	private:
		static void releaser(T *);

		std::shared_ptr<T> shared_impl_;
	};

	class common_token
	{
	public:
		explicit common_token(ANTLR3_COMMON_TOKEN *token)
			: impl_(token)
		{
		}

		std::string to_string();

		/* you're on your own using this, don't expect anything */
		ANTLR3_COMMON_TOKEN *get_implementation()
		{
			return impl_;
		}

	private:
		ANTLR3_COMMON_TOKEN *impl_;
	};

	class token_stream
	{
	public:
		explicit token_stream(lexer &);

		std::vector<common_token> get_tokens();

		/* you're on your own using this, don't expect anything */
		ANTLR3_COMMON_TOKEN_STREAM *get_implementation()
		{
			return shared_impl_.get();
		}

		lexer &get_lexer()
		{
			return lexer_;
		}

		lexer const &get_lexer() const
		{
			return lexer_;
		}

	private:
		static void releaser(ANTLR3_COMMON_TOKEN_STREAM *);

		std::shared_ptr<ANTLR3_COMMON_TOKEN_STREAM> shared_impl_;
		lexer lexer_;
	};

	class parser
	{
	public:
		explicit parser(token_stream &token_stream)
			: token_stream_(token_stream)
		{
		}

		virtual ~parser()
		{
		}

		token_stream &get_token_stream()
		{
			return token_stream_;
		}

		token_stream const &get_token_stream() const
		{
			return token_stream_;
		}

		/* you're on your own using this, don't expect anything */
		ANTLR3_PARSER *get_implementation()
		{
			return impl_;
		}

	protected:
		/* this has to be set by the deriving class */
		ANTLR3_PARSER *impl_;

	private:
		token_stream token_stream_;
	};

	template <class T>
	class parser_factory
		: public parser
	{
	public:
		template <class CreateFunction>
		parser_factory(CreateFunction const &create_function,
		               token_stream &token_stream);

	private:
		static void releaser(T *);

		std::shared_ptr<T> shared_impl_;
	};

}

#include "antlr3_cc.tcc"

#endif
