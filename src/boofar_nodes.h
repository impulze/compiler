#ifndef _BOOFAR_NODES_H_
#define _BOOFAR_NODES_H_

#include "boofar.h"

namespace boofar
{
	namespace nodes
	{
		class generic
		{
		public:
			virtual types::type get_type() const = 0;
			virtual std::string to_string() const = 0;

		private:
			std::string build_string(std::string value) const;
		};

		class identifier : generic
		{
			std::string name;

			identifier(std::string name);

			type get_type() const override;
		};
	};
};

#endif
