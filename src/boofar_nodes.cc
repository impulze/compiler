#include <sstream>
#include "boofar_nodes.h"

namespace boofar
{
	namespace nodes
	{
		// define type names
		// auto generic::type_names TODO report clang bug
		/*decltype(generic::tag_names) generic::tag_names
		{
			{ types::assignment, "assignment" },
			{ types::binary_operation, "binaryOperation" },
			{ types::dec_literal, "decimalLiteral" },
			{ types::float_literal, "floatLiteral" },
			{ types::identifier, "identifier" },
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

		// identifier
		const std::string &identifier::name() const
		{ return _name; }

		// literal
		const std::string &literal::constructor() const
		{ return _constructor; }

		// parameter_list
		const std::vector<declaration *> &parameter_list::parameters() const
		{ return _parameters; }

		// unary_operation
		const generic *unary_operation::expression() const
		{ return _expression; }

		const std::string &unary_operation::symbol() const
		{ return _symbol; }
	};
};
