#include "boofar_nodes.h"
#include "boofar_code_generator.h"

namespace boofar
{
	namespace visitors
	{
		void code_generator::visit(const nodes::assignment &node)
		{
			node.variable()->accept(*this);
			_output << " = ";
			node.expression()->accept(*this);
		}

		void code_generator::visit(const nodes::block &node)
		{
			_output << "{\n";
			for (const nodes::generic *statement: node.statements())
			{
				statement->accept(*this);
				_output << ";\n";
			}
			_output << "}\n";
		}

		void code_generator::visit(const nodes::declaration &node)
		{
			node.type()->accept(*this);
			_output << ' ';
			node.name()->accept(*this);
		}

		void code_generator::visit(const nodes::identifier &node)
		{ _output << node.name(); }
	}
}
