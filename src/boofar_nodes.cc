#include "boofar_nodes.h"

namespace boofar
{
	namespace nodes
	{
		identifier::identifier(std::string name):
			name(name)
		{}

		type identifier::get_type() const
		{ return type::identifier; }
	};
};
