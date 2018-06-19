#include "Array.h"
#include <iostream>
#include <fstream>
#include <stdarg.h>
using std::cout;
#include "String.h"

components::Array::Array()
{

}

components::Array::~Array()
{
}

const components::Component * components::Array::get(int at) const
{
	return this->values.getAt(at);
}

void components::Array::add(components::Component * value)
{
	this->values.add(value);
}

const unsigned int components::Array::size() const
{
	return this->values.count();
}

components::Component * components::Array::operator[](int index)
{
	return this->values.getAt(index);
}

const components::Component * components::Array::operator[](int index) const
{
	return this->values.getAt(index);
}

// override

void components::Array::print(std::ostream & out) const
{
	out << '[';
	if (this->values.count() > 0)
	{
		for (size_t i = 0; i < this->values.count() - 1; i++)
		{
			this->values.getAt(i)->print();
			out << ", ";
		}

		this->values.getAt(this->values.count() - 1)->print();
	}

	out << ']';
}
void components::Array::print() const
{
	this->print(cout);
}

components::ArrayCreator::ArrayCreator()
	:ComponentCreator("array")
{
}

components::Component * components::ArrayCreator::createComponent(std::ifstream & in) const
{
	return new Array();
}
