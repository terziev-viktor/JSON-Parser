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

components::Number::Number(const Number & other)
{
	this->value = other.value;
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

bool components::Number::tryParse(const char * str, int & out)
{
	int result = 0;
	int multiplier = 1;
	size_t len = strlen(str);
	for (size_t i = len - 1; i >= 0 ; --i)
	{
		if (str[i] <= '9' && str[i] >= '0')
		{
			result += (str[i] - 48) * multiplier;
			multiplier *= 10;
		}
		else
		{
			throw std::invalid_argument("String is not an integer");
		}
	}
	out = result;
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
	return *this == *other;
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

components::Component & components::Number::operator=(const Component * other)
{
	return *this = *other;
}

components::Component & components::Number::operator=(const Component & other)
{
	const Number & n = dynamic_cast<const Number&>(other);
	return *this = n;
}

components::Component * components::Number::copy() const
{
	Number * n = new Number(*this);
	return n;
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
