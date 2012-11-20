#include <sstream>
#include "boofar_nodes.h"

namespace boofar
{
	namespace nodes
	{
		// define type names
		// auto generic::type_names TODO report clang bug
		decltype(generic::tag_names) generic::tag_names
		{
			{ types::assignment, "assignment" },
			{ types::binary_operation, "binaryOperation" },
			{ types::dec_literal, "decimalLiteral" },
			{ types::float_literal, "floatLiteral" },
			{ types::identifier, "identifier" },
		};

		// assignment
		void assignment::append_inner_xml(std::ostream &buffer) const
		{
			buffer << "<left>" << *variable << "</left><right>" <<
				*expression << "</right>";
		}

		// binary operation
		void binary_operation::append_inner_xml(std::ostream &buffer) const
		{
			buffer << "<left>" << *left << "</left><operator>" << symbol <<
				"</operator><right>" << *right << "</right>";
		}

		// declaration
		void declaration::append_inner_xml(std::ostream &buffer) const
		{
			buffer << "<type>" << *type << "</type><name>" << *name <<
				"</name>";
		}

		// generic
		std::string generic::to_xml() const
		{
			std::ostringstream buffer;
			to_xml(buffer);
			return buffer.str();
		}

		std::ostream &generic::to_xml(std::ostream &buffer) const
		{
			buffer << '<' << tag_names[type] << '>';
			append_inner_xml(buffer);
			buffer << "</" << tag_names[type] << '>';
			return buffer;
		}

		// identifier
		void identifier::append_inner_xml(std::ostream &buffer) const
		{ buffer << name; }

		// literal
		void literal::append_inner_xml(std::ostream &buffer) const
		{ buffer << constructor; }

		// parameter_list
		void parameter_list::append_inner_xml(std::ostream &buffer) const
		{
			for (declaration *parameter: parameters)
			{ buffer << *parameter; }
		}
	};
};

// ostream extension
std::ostream &operator<<(std::ostream &stream,
	const boofar::nodes::generic &node)
{ return node.to_xml(stream); }
