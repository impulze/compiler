#ifndef _BOOFAR_NODES_H_
#define _BOOFAR_NODES_H_

#include "boofar_types.h"

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
		class generic
		{
		public:
			types::type get_type() const;
			std::string to_xml() const;
			std::ostream &to_xml(std::ostream &buffer) const;

		protected:
			generic(types::type type):
				type(type)
			{}
			virtual void append_inner_xml(std::ostream &buffer) const = 0;

		private:
			static std::unordered_map<int, std::string> tag_names;
			const types::type type;
		};

			class assignment : public generic
			{
			public:
				assignment(const identifier *variable,
					const generic *expression):
					
					generic(types::assignment), expression(expression),
						variable(variable)
				{}

			protected:
				void append_inner_xml(std::ostream &buffer) const override;

			private:
				const generic *expression;
				const identifier *variable;
			};

			class binary_operation : public generic
			{
			public:
				binary_operation(const std::string &symbol,
					const generic *left, const generic *right):
					
					generic(types::binary_operation), left(left), right(right),
						symbol(symbol)
				{}

			protected:
				void append_inner_xml(std::ostream &buffer) const override;

			private:
				const generic *left;
				const generic *right;
				const std::string symbol;
			};

			class identifier : public generic
			{
			public:
				identifier(const std::string &name):
					generic(types::identifier), name(name)
				{}

			protected:
				void append_inner_xml(std::ostream &buffer) const override;

			private:
				const std::string name;
			};

			class declaration : public generic
			{
			public:
				declaration(const identifier *type, const identifier *name):
					generic(types::declaration), name(name), type(type)
				{}

			protected:
				void append_inner_xml(std::ostream &buffer) const override;

			private:
				const identifier *name;
				const identifier *type;
			};

			class literal : public generic
			{
			protected:
				literal(types::type type, const std::string &constructor):
					generic(type), constructor(constructor)
				{}
				void append_inner_xml(std::ostream &buffer) const override;

			private:
				const std::string constructor;
			};

				class decimal_literal : public literal
				{
				public:
					decimal_literal(const std::string &constructor):
						literal(types::dec_literal, constructor) {}
				};

				class float_literal : public literal
				{
				public:
					float_literal(const std::string &constructor):
						literal(types::float_literal, constructor) {}
				};

				class hexadecimal_literal : public literal
				{
				public:
					hexadecimal_literal(const std::string &constructor):
						literal(types::hex_literal, constructor) {}
				};

				class octal_literal : public literal
				{
				public:
					octal_literal(const std::string &constructor):
						literal(types::oct_literal, constructor) {}
				};
			
			class parameter_list : public generic
			{
			public:
				parameter_list(const std::vector<declaration *> &&parameters):
					generic(types::parameter_list), parameters(parameters) {}

			protected:
				void append_inner_xml(std::ostream &buffer) const override;

			private:
				const std::vector<declaration *> parameters;
			};
	};
};

std::ostream &operator<<(std::ostream &stream,
		const boofar::nodes::generic &node);

#endif
