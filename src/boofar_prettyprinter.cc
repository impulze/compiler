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
			node.variable()->accept(*this);
			_output << "</variable><expression>";
			//visit(*node.expression()); TODO implement
			_output << "</expression></assignment>";
		}

		void prettyprinter::visit(const nodes::binary_operation &node)
		{
			_output << "<binary_operation symbol=\"" << node.symbol() <<
				"\"><left>";
			node.left()->accept(*this);
			_output << "</left><right>";
			node.right()->accept(*this);
			_output << "</right></binary_operation>";
		}

		void prettyprinter::visit(const nodes::declaration &node)
		{
			_output << "<declaration><type>";
			node.type()->accept(*this);
			_output << "</type><variable>";
			node.name()->accept(*this);
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

		void prettyprinter::visit(const nodes::program &node)
		{
			_output << "<program>";
			for (const nodes::generic *statement: node.statements())
			{
				_output << "<statement type=\"" << statement->type_string() <<
					"\">";
				statement->accept(*this);
				_output << "</statement>";
			}
			_output << "</program>";
		}

		void prettyprinter::visit(const nodes::unary_operation &node)
		{
			_output << "<unary_operation symbol=\"" << node.symbol() <<
				"\"><operand>";
			node.accept(*this);
			_output << "</operand></unary_operation>";
		}
	}
}
