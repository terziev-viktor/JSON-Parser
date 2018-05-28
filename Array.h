#pragma once

#include "Component.h"
#include "tools\List.hpp"
using tools::List;

namespace components
{
	class Array : public Component
	{
	public:
		Array();
		~Array();

		const Component * get(int at) const;
		void add(Component * value);
		const unsigned int size() const;

		void print() const;
	private:
		List<Component> values;
	};
}
