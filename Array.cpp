#include "Array.h"
#include <iostream>
#include <stdarg.h>
using std::cout;

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

// override
void components::Array::print() const
{
	cout << '[';
	for (unsigned int i = 0; i < this->values.count() - 1; i++)
	{
		this->values.getAt(i)->print();
		cout << ", ";
	}
	this->values.getAt(this->values.count() - 1)->print();
	cout << ']';
}


