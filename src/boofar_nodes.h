#ifndef _BOOFAR_NODES_H_
#define _BOOFAR_NODES_H_

#include "boofar_types.h"
#include "boofar_base_acceptor.h"

#include <unordered_map>
#include <string>

namespace boofar
{
	namespace nodes
	{
		class generic
			: public acceptors::base<>
		{
		public:
			virtual std::string get_string_value() const = 0;
			types::type get_type() const;
			std::string to_string() const;

		protected:
			generic(types::type type)
				: type(type)
			{
			}

		private:
			static std::unordered_map<int, std::string> type_names;
			const types::type type;
		};

		class identifier
			: public acceptors::implementation<identifier>,
			  public generic
		{
		public:
			identifier(const std::string &name)
				: generic(types::identifier),
				  name(name)
			{
			}

			std::string get_string_value() const override;

		private:
			std::string name;
		};

		class declaration
			: public acceptors::implementation<declaration>,
			  public generic
		{
		public:
			declaration(const identifier *type, const identifier *name)
				: generic(types::declaration),
				  name(name),
				  type(type)
			{
			}

			std::string get_string_value() const override;

		private:
			const identifier *name;
			const identifier *type;
		};

		class literal
			: public generic
		{
		public:
			std::string get_string_value() const override;

		protected:
			literal(types::type type, const std::string &constructor):
				generic(type), constructor(constructor) {}

		private:
			std::string constructor;
		};

		class decimal_literal
			: /*public acceptors::implementation<generic, decimal_literal>,*/
			  public literal
		{
		public:
			decimal_literal(const std::string &constructor):
				literal(types::dec_literal, constructor) {}
		};

		class float_literal
			: /*public acceptors::implementation<generic, float_literal>,*/
			  public literal
		{
		public:
			float_literal(const std::string &constructor):
				literal(types::float_literal, constructor) {}
		};

		class hexadecimal_literal
			: /*public acceptors::implementation<generic, hexadecimal_literal>,*/
			  public literal
		{
		public:
			hexadecimal_literal(const std::string &constructor):
				literal(types::hex_literal, constructor) {}
		};

		class octal_literal
			: /*public acceptors::implementation<generic, octal_literal>,*/
			  public literal
		{
		public:
			octal_literal(const std::string &constructor):
				literal(types::oct_literal, constructor) {}
		};
	};
};

#endif
