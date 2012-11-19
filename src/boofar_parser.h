#ifndef BOOFAR_PARSER_H_INCLUDED
#define BOOFAR_PARSER_H_INCLUDED

#include "boofar_parser.hpp"

namespace boofar
{
	struct parser
		: generated::boofar_parser
	{
		template <class... Args>
		parser(Args &&... args)
			: generated::boofar_parser(std::forward<Args>(args)...)
		{
		}
	};
}

#endif
