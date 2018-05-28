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

		const char * get(int at) const;
		void add(const char * value);
		const unsigned int size() const;

		void print() const;
	private:
		List<const char> values;
	};
}
