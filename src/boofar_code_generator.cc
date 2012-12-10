#include "boofar_nodes.h"
#include "boofar_code_generator.h"
#include "help_indent_printer.h"

namespace boofar
{
	namespace visitors
	{
		void code_generator::visit(const nodes::assignment &node)
		{
			node.variable()->accept(*this);

			auto p = help::indent_printer(_output, _indent);

			p.no_indent() << " = ";

			node.expression()->accept(*this);
		}

		void code_generator::visit(const nodes::block &node)
		{
			auto p = help::indent_printer(_output, _indent);
			p << "{\n";
			++p;

			for (const nodes::generic *statement: node.statements())
			{
				p.indent();
				statement->accept(*this);
				p.no_indent() << ";\n";
			}

			--p;
			p << "}\n";
		}

		void code_generator::visit(const nodes::declaration &node)
		{
			node.type()->accept(*this);

			auto p = help::indent_printer(_output, _indent);

			p.no_indent() << ' ';

			node.name()->accept(*this);
		}

		void code_generator::visit(const nodes::identifier &node)
		{
			auto p = help::indent_printer(_output, _indent);

			p.no_indent() << node.name();
		}
	}
}
