#include "boofar_nodes.h"
#include "boofar_prettyprinter.h"
#include "boofar_code_generator.h"

namespace boofar
{
	namespace visitors
	{
		void prettyprinter::visit(nodes::declaration &node)
		{
			output_ << "visited declaration node: " << node << '\n';
		}

		void prettyprinter::visit(nodes::identifier &node)
		{
			output_ << "visited identifier node: " << node << '\n';
		}
	}
}
