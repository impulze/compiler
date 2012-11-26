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
			visit(node.variable());
			_output << "</variable><expression>";
			//visit(node.expression()); TODO implement
			_output << "</expression></assignment>";
		}

		void prettyprinter::visit(const nodes::declaration &node)
		{
			_output << "<declaration><type>";
			visit(node.type());
			_output << "</type><variable>";
			visit(node.name());
			_output << "</variable></declaration>";
		}

		void prettyprinter::visit(const nodes::identifier &node)
		{ _output << "<identifier name=\"" << node.name() << "\"/>"; }
	}
}
