#pragma once
#include "Number.h"
#include <math.h>
using components::Number;

const double Number::EPS = 1e-15;
static const components::creators::NumberCreator theNumberCreator;

Number::Number():value(0.0)
{

}

components::Number::Number(const cstring & other)
{
	this->set_value(other);
}

components::Number::Number(const double v)
{
	this->set_value(v);
}

const double components::Number::get_value() const
{
	return this->value;
}

void components::Number::set_value(const cstring & str)
{
	char * end;
	const char * str_num = str.get_as_char_array();
	this->value = strtod(str_num, &end);
	if (end == str_num)
	{
		throw bad_cast_exception("cstring", "Number");
	}
}

void components::Number::set_value(const double v)
{
	this->value = v;
}

Number & components::Number::operator=(const double value)
{
	this->set_value(value);
	return *this;
}

bool components::Number::operator<(const Number & other) const
{
	if (this->value < 0 && other.value > 0)
	{
		return true;
	}
	if (this->value > 0 && other.value < 0)
	{
		return false;
	}
	double diff;
	if (this->value > 0)
	{
		diff = (abs(this->value) - (other.get_value()));
	}
	else
	{
		diff = abs(abs(this->value) - abs(other.get_value()));
	}
	return diff < 0;
}

bool components::Number::operator<=(const Number & other) const
{
	return !(*this > other);
}

bool components::Number::operator>(const Number & other) const
{
	return !(*this < other);
}

bool components::Number::operator>=(const Number & other) const
{
	return !(*this < other);
}

bool components::Number::operator==(const Number & other) const
{
	if (this->value < 0 && other.value > 0)
	{
		return false;
	}
	if (this->value > 0 && other.value < 0)
	{
		return false;
	}
	double diff = abs(abs(this->value) - abs(other.get_value()));
	return diff < EPS;
}

components::Component * components::Number::copy() const
{
	Number * n = new Number(*this);
	return n;
}

const unsigned int components::Number::size() const
{
	return fabs(this->get_value());
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

void components::Number::print(std::ostream & out, bool pretty, unsigned int tab_index) const
{
	out << this->value;
}

bool components::Number::equals(const Component & other) const
{
	return false;
}

cstring components::Number::tell_type() const
{
	return "Number";
}

Number components::operator+(const Number & a, const Number & b)
{
	Number n(a);
	n += b;
	return n;
}

std::ostream & components::operator<<(std::ostream & os, const Number & n)
{
	os << n.get_value();
	return os;
}

components::Component * components::creators::NumberCreator::createComponent(TokensSimulator & tokens, unsigned int & line_number) const
{
	Number * result = nullptr;
	tokens.save_pos();
	char c = tokens.get();
	cstring str(10);
	while ((c >= '0' && c <= '9') || (c == '-' || c == '.'))
	{
		str += c;
		tokens.next();
		if (tokens.is_done())
		{
			break;
		}
		c = tokens.get();
	}
	if (str.get_length() == 0)
	{
		tokens.revert();
		return nullptr;
	}
	try
	{
		result = new Number(str);
	}
	catch (const std::exception&)
	{
		tokens.revert();
		return nullptr;
	}
	return result;

}
