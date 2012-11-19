#ifndef BOOFAR_LEXER_H_INCLUDED
#define BOOFAR_LEXER_H_INCLUDED

#include "boofar_lexer.hpp"

#include <utility>

namespace boofar
{
	struct lexer
		: generated::boofar_lexer
	{
		template <class... Args>
		lexer(Args &&... args)
			: generated::boofar_lexer(std::forward<Args>(args)...)
		{
		}
	};
}

#endif
