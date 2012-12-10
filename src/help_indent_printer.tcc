#include "help_indent_printer.h"

namespace help
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
