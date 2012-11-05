#ifndef _BOOFAR_NODES_H_
#define _BOOFAR_NODES_H_

#include "boofar.h"

namespace boofar
{
	namespace nodes
	{
		class identifier : generic
		{
			std::string name;

			identifier(std::string name);

			type get_type() const override;
		};
	};
};

#endif
