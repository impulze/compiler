#include "boofar_nodes.h"
#include "boofar_prettyprinter.h"
#include "boofar_code_generator.h"

namespace
{
	struct indent_printer
	{
		explicit indent_printer(std::ostream &strm, int &indent)
			: strm_(strm),
			  indent_(indent),
			  once_(false),
			  no_indent_(false)
		{
		}

		indent_printer &once()
		{
			once_ = true;
			return *this;
		}

		template <class T>
		indent_printer &operator<<(T const &);

		indent_printer &operator++()
		{
			indent_++;
			once_ = no_indent_ = false;
			return *this;
		}

		indent_printer &operator--()
		{
			indent_--;
			once_ = no_indent_ = false;
			return *this;
		}

		std::ostream &strm_;
		int &indent_;
		bool once_;
		bool no_indent_;
	};
}

namespace boofar
{
	namespace visitors
	{
		void prettyprinter::visit(const nodes::assignment &node)
		{
			auto p = indent_printer(_output, _indent);

			p.once() << "<assignment>\n";
			++p;
			p << "<variable>\n";
			++p;
			node.variable()->accept(*this);
			--p;
			p << "</variable>\n";
			p << "<expression>\n";
			++p;
			node.expression()->accept(*this);
			--p;
			p << "</expression>\n";
			--p;
			p << "</assignment>\n";
		}

		void prettyprinter::visit(const nodes::binary_operation &node)
		{
			auto p = indent_printer(_output, _indent);

			p.once() << "<binary_operation symbol=\"" << node.symbol() << "\">\n";
			++p;
			p << "<left>\n";
			++p;
			node.left()->accept(*this);
			--p;
			p << "</left>\n";
			p << "<right>\n";
			++p;
			node.right()->accept(*this);
			--p;
			p << "</right>\n";
			--p;
			p << "</binary_operation>\n";
		}

		void prettyprinter::visit(const nodes::block &node)
		{
			auto p = indent_printer(_output, _indent);

			p.once() << "<block>\n";
			++p;

			for (const nodes::generic *statement: node.statements())
			{
				p.once() << "<statement type=\"" << statement->type_string() << "\">\n";
				++p;
				statement->accept(*this);
				--p;
				p << "</statement>\n";
			}

			--p;
			p << "</block>\n";
		}

		void prettyprinter::visit(const nodes::condition &node)
		{
			auto p = indent_printer(_output, _indent);

			p.once() << "<condition>\n";
			++p;
			p << "<expression>\n";
			++p;
			node.expression()->accept(*this);
			--p;
			p << "</expression>\n";
			p << "<trueBlock>\n";
			++p;
			node.true_block()->accept(*this);
			--p;
			p << "</trueBlock>\n";
			p << "<falseBlock>\n";
			++p;
			node.false_block()->accept(*this);
			--p;
			p << "</falseBlock>\n";
			--p;
			p << "</condition>\n";
		}

		void prettyprinter::visit(const nodes::declaration &node)
		{
			auto p = indent_printer(_output, _indent);

			p.once() << "<declaration>\n";
			++p;
			p << "<type>\n";
			++p;
			node.type()->accept(*this);
			--p;
			p << "</type>\n";
			p << "<variable>\n";
			++p;
			node.name()->accept(*this);
			--p;
			p << "</variable>\n";
			--p;
			p << "</declaration>\n";
		}

		void prettyprinter::visit(const nodes::identifier &node)
		{
			auto p = indent_printer(_output, _indent);

			p.once() << "<identifier name=\"" << node.name() << "\"/>\n";
		}

		void prettyprinter::visit(const nodes::literal &node)
		{
			auto p = indent_printer(_output, _indent);

			p.once() << "<literal type=\"";

			switch (node.type())
			{
				case type::dec_literal:
					p << "decimal";
					break;
				case type::float_literal:
					p << "float";
					break;
				case type::hex_literal:
					p << "hexadecimal";
					break;
				case type::oct_literal:
					p << "octal";
					break;
				default:
					p << "unknown";
			}

			p << "\" constructor=\"" << node.constructor() << "\"/>\n";
		}

		void prettyprinter::visit(const nodes::null &node)
		{
			auto p = indent_printer(_output, _indent);
			p.once() << "<null/>";
		}

		void prettyprinter::visit(const nodes::unary_operation &node)
		{
			auto p = indent_printer(_output, _indent);

			p.once() << "<unary_operation symbol=\"" << node.symbol() << "\">\n";
			++p;
			p << "<operand>\n";
			++p;
			node.expression()->accept(*this);
			--p;
			p << "</operand>\n";
			--p;
			p << "</unary_operation>\n";
		}
	}
}

namespace
{
	template <class T>
	indent_printer &indent_printer::operator<<(T const &t)
	{
		if (!no_indent_)
		{
			for (int i = 0; i < indent_; i++)
			{
				strm_ << "  ";
			}
		}

		if (once_)
		{
			no_indent_ = true;
			once_ = false;
		}

		strm_ << t;

		return *this;
	}
}
