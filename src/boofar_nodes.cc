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
			{ types::assignment, "assignment" },
			{ types::binary_operation, "binary operation" },
			{ types::dec_literal, "decimal literal" },
			{ types::float_literal, "float literal" },
			{ types::identifier, "identifier" },
		};

		// assignment
		std::string assignment::get_string_value() const
		{ return variable->get_string_value() + "=" + expression->get_string_value(); }

		// binary operation
		std::string binary_operation::get_string_value() const
		{ return left->get_string_value() + symbol + right->get_string_value(); }

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

		// parameter_list
		std::string parameter_list::get_string_value() const
		{
			std::ostringstream buffer;
			for (declaration *parameter: parameters)
			{ buffer << parameter->get_string_value() << ','; }

			std::string result = buffer.str();
			result.erase(result.cend() - 1);

			return result;
		}
	};
};
