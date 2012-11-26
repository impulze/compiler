#include <sstream>
#include "boofar_nodes.h"

namespace boofar
{
	namespace nodes
	{
		// define type names
		// auto generic::type_names TODO report clang bug
		/*decltype(generic::type_names) generic::type_names
		{
			{ types::assignment, "assignment" },
			{ types::binary_operation, "binaryOperation" },
			{ types::declaration, "declaration" },
			{ types::dec_literal, "decimalLiteral" },
			{ types::float_literal, "floatLiteral" },
			{ types::hex_literal, "hexadecimalLiteral" },
			{ types::identifier, "identifier" },
			{ types::program, "program" },
			{ types::unary_operation, "unaryOperation" },
		};*/

		// assignment
		const generic *assignment::expression() const
		{ return _expression; }
		
		const identifier *assignment::variable() const
		{ return _variable; }

		// binary_operation
		const generic *binary_operation::left() const
		{ return _left; }

		const generic *binary_operation::right() const
		{ return _right; }

		const std::string &binary_operation::symbol() const
		{ return _symbol; }

		// declaration
		const identifier *declaration::name() const
		{ return _name; }

		const identifier *declaration::type() const
		{ return _type; }

		// generic
		types::type generic::type() const
		{ return _type; }

		const char *generic::type_string() const
		{ return type_to_string(_type); }

		const char *generic::type_to_string(types::type type)
		{
			switch (type)
			{
				case types::assignment: return "assignment";
				case types::binary_operation: return "binary_operation";
				case types::declaration: return "declaration";
				case types::dec_literal: return "decimal_literal";
				case types::float_literal: return "float_literal";
				case types::hex_literal: return "hexadecimal_literal";
				case types::identifier: return "identifier";
				case types::program: return "program";
				case types::unary_operation: return "unary_operation";
				default: return "unknown";
			}
		}

		// identifier
		const std::string &identifier::name() const
		{ return _name; }

		// literal
		const std::string &literal::constructor() const
		{ return _constructor; }

		// parameter_list
		const std::vector<declaration *> &parameter_list::parameters() const
		{ return _parameters; }

		// program
		const std::vector<generic *> &program::statements() const
		{ return _statements; }

		// unary_operation
		const generic *unary_operation::expression() const
		{ return _expression; }

		const std::string &unary_operation::symbol() const
		{ return _symbol; }
	};
};
