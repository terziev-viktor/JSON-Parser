#pragma once

#include "Component.h"
#include "tools\List.hpp"
//using factory::ComponentCreator;
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
		Component * operator[](unsigned int index);
		const Component * operator[](unsigned int index) const;

		void print(unsigned short tab_index = 0) const;
		void print(std::ostream & out, unsigned short tab_index = 0) const;
	private:
		List<Component> values;
	};

	class ArrayCreator :public ComponentCreator
	{
	public:
		ArrayCreator();
		Component * createComponent(Vector<Token>::Iterator & i, unsigned int & line_number) const;
	};

	static ArrayCreator theArrayCreator;
}
