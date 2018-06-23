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
		Component * operator[](int index);
		const Component * operator[](int index) const;

		void print() const;
		void print(std::ostream & out) const;
	private:
		List<Component> values;
	};

	class ArrayCreator :public ComponentCreator
	{
	public:
		ArrayCreator();
		Component * createComponent(Vector<Token>::Iterator & i) const;
	};

	static ArrayCreator theArrayCreator;
}
