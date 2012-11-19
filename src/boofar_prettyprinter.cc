#include "boofar_nodes.h"
#include "boofar_prettyprinter.h"

namespace boofar
{
	namespace visitors
	{
		void prettyprinter::visit(boofar::nodes::generic &node)
		{
			output_ << "visited generic node: " << node.to_string() << '\n';
		}
	}
}
