#ifndef BOOFAR_TYPES_H_INCLUDED
#define BOOFAR_TYPES_H_INCLUDED

namespace boofar
{
	namespace types
	{
		enum type
		{
			comment,
			dec_literal,
			float_literal,
			hex_literal,
			identifier,
			newline,
			oct_literal,
			//string_literal,

			// FIXME the following types are not associated with an antlr makro
			atomic_expression,
			declaration,
		};
	}

	typedef types::type type;
}

#endif
