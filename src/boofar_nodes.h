#ifndef _BOOFAR_NODES_H_
#define _BOOFAR_NODES_H_

#include <unordered_map>
#include "boofar_types.h"

namespace boofar
{
	namespace nodes
	{

		class generic
		{
		public:
			virtual std::string get_string_value() const = 0;
			types::type get_type() const;
			std::string to_string() const;

		protected:
			generic(types::type type);

		private:
			static std::unordered_map<int, std::string> type_names;
			const types::type type;
		};

		class identifier : generic
		{
		public:
			identifier(const std::string &name);
			std::string get_string_value() const override;

		private:
			std::string name;
		};

			class declaration : generic
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

		class literal : generic
		{
		public:
			std::string get_string_value() const override;

		protected:
			literal(types::type type, const std::string &constructor):
				generic(type), constructor(constructor) {}

		private:
			std::string constructor;
		};

			class decimal_literal : public literal
			{
			public:
				decimal_literal(const std::string &constructor):
					literal(types::dec_literal, constructor) {}
			};

			class float_literal : literal
			{
			public:
				float_literal(const std::string &constructor):
					literal(types::float_literal, constructor) {}
			};

			class hexadecimal_literal : literal
			{
			public:
				hexadecimal_literal(const std::string &constructor):
					literal(types::hex_literal, constructor) {}
			};

			class octal_literal : literal
			{
			public:
				octal_literal(const std::string &constructor):
					literal(types::oct_literal, constructor) {}
			};
	};
};

#endif
