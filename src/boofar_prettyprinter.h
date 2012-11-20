#ifndef BOOFAR_PRETTYPRINTER_H_INCLUDED
#define BOOFAR_PRETTYPRINTER_H_INCLUDED

#include "boofar_base_visitor.h"

#include <ostream>

namespace boofar
{
	namespace visitors
	{
		class prettyprinter
			: public base<>
		{
		public:
			prettyprinter(std::ostream &output)
				: output_(output)
			{
			}

			using base<>::visit;

			void visit(nodes::declaration &node) override;
			void visit(nodes::identifier &node) override;

		private:
			std::ostream &output_;
		};
	}
}

#endif
