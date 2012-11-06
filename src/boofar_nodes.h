#ifndef _BOOFAR_NODES_H_
#define _BOOFAR_NODES_H_

#include <unordered_map>
#include "boofar.h"

namespace boofar
{
	namespace nodes
	{

		class generic
		{
		public:
			types::type get_type() const;
			std::string to_string() const;

		protected:
			generic(types::type type);

		private:
			static std::unordered_map<int, std::string> type_names;
			const types::type type;
			virtual std::string get_string_value() const = 0;
		};

		class identifier : generic
		{
		public:
			identifier(const std::string &name);

		private:
			std::string name;
			std::string get_string_value() const override;
		};

		class literal : generic
		{
		protected:
			literal(types::type type, const std::string &constructor);

		private:
			std::string constructor;
			std::string get_string_value() const override;
		};

		class decimal_literal : literal
		{
		public:
			decimal_literal(const std::string &constructor);
		};
	};
};

#endif
