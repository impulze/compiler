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
				_output(output), _indent(0)
			{}

			using base<>::visit;

			void visit(const nodes::assignment &node) override;
			void visit(const nodes::binary_operation &node) override;
			void visit(const nodes::block &node) override;
			void visit(const nodes::condition &node) override;
			void visit(const nodes::declaration &node) override;
			void visit(const nodes::identifier &node) override;
			void visit(const nodes::literal &node) override;
			void visit(const nodes::null &node) override;
			void visit(const nodes::unary_operation &node) override;

		private:
			std::ostream &_output;
			int _indent;
		};
	}
}

#endif
