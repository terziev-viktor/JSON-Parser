#include "Number.h"
#include "String.h"
#include <iostream>
#include <math.h>

using std::cout;
using components::Number;
using components::String;

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

bool components::Number::operator==(const Component * other) const
{
	const Number * casted = dynamic_cast<const Number*>(other);
	if (casted)
	{
		return *this == *casted;
	}
	return false;
}

bool components::Number::operator==(const Component & other) const
{
	try
	{
		const Number & casted = dynamic_cast<const Number&>(other);
		return *this == casted;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

components::Component & components::Number::operator=(Component * other)
{
	Number * n = dynamic_cast<Number*>(other);
	if (n)
	{
		*this = *n;
	}
	else
	{
		String * s = dynamic_cast<String*>(other);
		if (s)
		{
			this->value = std::stod(s->getValue());
		}
	}
	return *this;
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

void components::Number::print(unsigned short tab_index, bool pretty) const
{
	print(cout, tab_index, pretty);
}

void components::Number::print(std::ostream & out, unsigned short tab_index, bool pretty) const
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
