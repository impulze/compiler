#ifndef BOOFAR_CODE_GENERATOR_H_INCLUDED
#define BOOFAR_CODE_GENERATOR_H_INCLUDED

#include "boofar_base_visitor.h"

namespace boofar
{
	namespace visitors
	{
		class code_generator
			: public base<>
		{
		public:
			using base<>::visit;

			void visit(nodes::declaration const &node) override;
		};
	}
}

#endif
