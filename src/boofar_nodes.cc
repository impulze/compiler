#include <sstream>
#include "boofar_nodes.h"

namespace boofar
{
	namespace nodes
	{
		// define type names
		// auto generic::type_names TODO report clang bug
		decltype(generic::type_names) generic::type_names
		{
			{ types::dec_literal, "decimal literal" },
			{ types::float_literal, "float literal" },
			{ types::identifier, "identifier" },
		};

		// declaration
		std::string declaration::get_string_value() const
		{ return type->get_string_value() + " " + name->get_string_value(); }

		// generic
		std::string generic::to_string() const
		{
			std::ostringstream strm;
			strm << '<' << type_names[type] << ':' <<
				get_string_value() << '>';
			return strm.str();
		}

		// identifier
		std::string identifier::get_string_value() const
		{ return name; }

		// literal
		std::string literal::get_string_value() const
		{ return constructor; }
	};
};
