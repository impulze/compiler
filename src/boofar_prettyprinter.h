#ifndef BOOFAR_PRETTYPRINTER_H_INCLUDED
#define BOOFAR_PRETTYPRINTER_H_INCLUDED

#include "boofar_base_visitor.h"

#include <ostream>

namespace boofar
{
	namespace visitors
	{
		class prettyprinter
			: public visitors::base<>
		{
		public:
			prettyprinter(std::ostream &output)
				: output_(output)
			{
			}

			void visit(boofar::nodes::generic &node) override;

		private:
			std::ostream &output_;
		};
	}
}

#endif

