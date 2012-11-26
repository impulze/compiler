#ifndef BOOFAR_PRETTYPRINTER_H_INCLUDED
#define BOOFAR_PRETTYPRINTER_H_INCLUDED

#include "boofar_base_visitor.h"

#include <ostream>

namespace boofar
{
	namespace visitors
	{
		class prettyprinter : public base<>
		{
		public:
			prettyprinter(std::ostream &output) :
				_output(output)
			{}

			using base<>::visit;

			void visit(const nodes::assignment &node) override;
			void visit(const nodes::declaration &node) override;
			void visit(const nodes::identifier &node) override;

		private:
			std::ostream &_output;
		};
	}
}

#endif
