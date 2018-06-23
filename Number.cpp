#include "Number.h"
#include <iostream>
#include <math.h>

using std::cout;
using components::Number;

const double Number::EPS = 1e-15;

Number::Number()
{
}

components::Number::Number(const string & str)
{
	this->value = stod(str);
}

components::Number::Number(const double v)
{
	this->value = v;
}


Number::~Number()
{
}

void components::Number::setValue(double v)
{
	this->value = v;
}

const double components::Number::getValue() const
{
	return this->value;
}

Number & components::Number::operator=(const Number & other)
{
	this->value = other.value;
	return *this;
}

bool components::Number::operator<(const Number & other) const
{
	double diff = this->value - other.getValue();
	return diff < 0;
}

bool components::Number::operator>(const Number & other) const
{
	double diff = this->value - other.getValue();
	return diff > 0;
}

bool components::Number::operator==(const Number & other) const
{
	double diff = this->value - other.getValue();
	diff = fabs(diff);
	return diff < Number::EPS;
}

Number & components::Number::operator+=(const Number & other)
{
	this->value += other.value;
	return *this;
}

Number & components::Number::operator-=(const Number & other)
{
	this->value -= other.value;
	return *this;
}

Number & components::Number::operator*=(const Number & other)
{
	this->value *= other.value;
	return *this;
}

Number & components::Number::operator/=(const Number & other)
{
	this->value /= other.value;
	return *this;
}

void components::Number::print(unsigned short tab_index) const
{
	print(cout);
}

void components::Number::print(std::ostream & out, unsigned short tab_index) const
{
	out << value;
}

components::Component * components::Number::operator[](unsigned int index)
{
	return this;
}

const components::Component * components::Number::operator[](unsigned int index) const
{
	return this;
}
