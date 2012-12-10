#ifndef HELP_INDENT_PRINTER_H_INCLUDED
#define HELP_INDENT_PRINTER_H_INCLUDED

namespace help
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

#include "help_indent_printer.tcc"

#endif
