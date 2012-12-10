#ifndef BOOFAR_CODE_GENERATOR_H_INCLUDED
#define BOOFAR_CODE_GENERATOR_H_INCLUDED

#include "boofar_base_visitor.h"

#include <ostream>

namespace boofar
{
	namespace visitors
	{
		class code_generator
			: public base<>
		{
		public:
			code_generator(std::ostream &output) :
				_output(output)
			{}

			using base<>::visit;

			void visit(nodes::declaration const &node) override;

		private:
			std::ostream &_output;
		};
	}
}

#endif
