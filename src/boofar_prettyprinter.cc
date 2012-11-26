#include "boofar_nodes.h"
#include "boofar_prettyprinter.h"
#include "boofar_code_generator.h"

namespace boofar
{
	namespace visitors
	{
		void prettyprinter::visit(const nodes::assignment &node)
		{
			_output << "<assignment><variable>";
			visit(*node.variable());
			_output << "</variable><expression>";
			//visit(*node.expression()); TODO implement
			_output << "</expression></assignment>";
		}

		void prettyprinter::visit(const nodes::binary_operation &node)
		{
			_output << "<binary_operation symbol=\"" << node.symbol() <<
				"\"><left>";
			visit(*node.left());
			_output << "</left><right>";
			visit(*node.right());
			_output << "</right></binary_operation>";
		}

		void prettyprinter::visit(const nodes::declaration &node)
		{
			_output << "<declaration><type>";
			visit(*node.type());
			_output << "</type><variable>";
			visit(*node.name());
			_output << "</variable></declaration>";
		}

		void prettyprinter::visit(const nodes::identifier &node)
		{ _output << "<identifier name=\"" << node.name() << "\"/>"; }

		void prettyprinter::visit(const nodes::literal &node)
		{
			_output << "<literal type=\"";
			switch (node.type())
			{
				case type::dec_literal:
					_output << "decimal";
					break;
				case type::float_literal:
					_output << "float";
					break;
				case type::hex_literal:
					_output << "hexadecimal";
					break;
				case type::oct_literal:
					_output << "octal";
					break;
				default:
					_output << "unknown";
			}
			_output << "\" constructor=\"" << node.constructor() << "\"/>";
		}

		void prettyprinter::visit(const nodes::unary_operation &node)
		{
			_output << "<unary_operation symbol=\"" << node.symbol() <<
				"\"><operand>";
			visit(*node.expression());
			_output << "</operand></unary_operation>";
		}
	}
}
