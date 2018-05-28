#include "Number.h"
#include <iostream>
#include <math.h>

using std::cout;
using components::Number;

const double Number::EPS = 1e-15;

Number::Number()
{
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


void components::Number::print() const
{
	cout << value;
}
