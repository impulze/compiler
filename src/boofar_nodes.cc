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
			{ types::type::dec_literal, "decimal literal" },
			{ types::type::identifier, "identifier" }
		};

		// generic
		generic::generic(types::type type):
			type(type)
		{}

		std::string generic::to_string() const
		{
			return (std::ostringstream() << '<' << type_names[type] << ':' <<
				get_string_value() << '>').str();
		}

		// identifier
		identifier::identifier(const std::string &name):
			generic(types::type::identifier), name(name)
		{}

		std::string identifier::get_string_value() const
		{ return name; }

		// literal
		literal::literal(types::type type, const std::string &constructor):
			generic(type), constructor(constructor)
		{}

		std::string literal::get_string_value() const
		{ return constructor; }

		// decimal_literal
		decimal_literal::decimal_literal(const std::string &constructor):
			literal(types::type::dec_literal, constructor)
		{}
	};
};
