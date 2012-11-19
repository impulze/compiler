#ifndef BOOFAR_TRAITS_H_INCLUDED
#define BOOFAR_TRAITS_H_INCLUDED

#include <antlr3.hpp>

namespace generated
{
	class boofar_lexer;
	class boofar_parser;
}

namespace boofar
{
	typedef antlr3::Traits<generated::boofar_lexer, generated::boofar_parser> traits;
}

typedef boofar::traits boofar_lexerTraits;
typedef boofar::traits boofar_parserTraits;

#endif
