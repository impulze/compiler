#ifndef _BOOFAR_NODES_H_
#define _BOOFAR_NODES_H_

#include "boofar_types.h"
#include "boofar_base_acceptor.h"

#include <unordered_map>
#include <string>
#include <vector>

namespace boofar
{
	namespace nodes
	{
		// forwardings
		class identifier;

		// declarations
		class generic : public acceptors::base<>
		{
		public:
			types::type type() const;

		protected:
			generic(types::type type) :
				_type(type)
			{}

		private:
			const types::type _type;
		};

		class assignment :
			public acceptors::implementation<assignment>, public generic
		{
		public:
			assignment(const identifier *variable, const generic *expression) :
				generic(types::assignment), _expression(expression),
				_variable(variable)
			{}

			const generic *expression() const;
			const identifier *variable() const;

		private:
			const generic *_expression;
			const identifier *_variable;
		};

		class binary_operation :
			public acceptors::implementation<binary_operation>, public generic
		{
		public:
			binary_operation(const std::string &symbol, const generic *left,
				const generic *right) :
				
				generic(types::binary_operation), _left(left), _right(right),
				_symbol(symbol)
			{}

			const generic *left() const;
			const generic *right() const;
			const std::string &symbol() const;

		private:
			const generic *_left;
			const generic *_right;
			const std::string _symbol;
		};

		class identifier :
			public acceptors::implementation<identifier>, public generic
		{
		public:
			identifier(const std::string &name) :
				generic(types::identifier), _name(name)
			{}

			const std::string &name() const;

		private:
			const std::string _name;
		};

		class declaration :
			public acceptors::implementation<declaration>, public generic
		{
		public:
			declaration(const identifier *type, const identifier *name) :
				generic(types::declaration), _name(name), _type(type)
			{}

			const identifier *name() const;
			const identifier *type() const;

		private:
			const identifier *_name;
			const identifier *_type;
		};

		class literal : public generic
		{
		public:
			const std::string &constructor() const;

		protected:
			literal(types::type type, const std::string &constructor) :
				generic(type), _constructor(constructor)
			{}

		private:
			const std::string _constructor;
		};

		class decimal_literal :
			public acceptors::implementation<decimal_literal>, public literal
		{
		public:
			decimal_literal(const std::string &constructor) :
				literal(types::dec_literal, constructor)
			{}
		};

		class float_literal :
			public acceptors::implementation<float_literal>, public literal
		{
		public:
			float_literal(const std::string &constructor) :
				literal(types::float_literal, constructor)
			{}
		};

		class hexadecimal_literal :
			public acceptors::implementation<hexadecimal_literal>,
			public literal
		{
		public:
			hexadecimal_literal(const std::string &constructor) :
				literal(types::hex_literal, constructor)
			{}
		};

		class octal_literal :
			public acceptors::implementation<octal_literal>, public literal
		{
		public:
			octal_literal(const std::string &constructor) :
				literal(types::oct_literal, constructor)
			{}
		};

		class parameter_list :
			public acceptors::implementation<parameter_list>, public generic
		{
		public:
			parameter_list(const std::vector<declaration *> &parameters) :
				generic(types::parameter_list), _parameters(parameters)
			{}

			const std::vector<declaration *> &parameters() const;

		private:
			const std::vector<declaration *> _parameters;
		};
	};
};

#endif
