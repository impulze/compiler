#include "boofar_nodes.h"
#include "boofar_code_generator.h"

#include <iostream>

namespace boofar
{
	namespace visitors
	{
		void code_generator::visit(nodes::declaration &node)
		{
			using std::cout;
			cout << "codegen declaration node\n";
		}
	}
}
