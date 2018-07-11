#pragma once
#include "cstring.h"
#include <string.h>
#include <stdexcept>
#include <iostream>
using namespace tools;
cstring::cstring() :length(0), capacity(1), value(nullptr)
{
	this->value = new char[this->capacity];
	this->value[0] = '\0';
}

cstring::cstring(unsigned int length) :length(0), capacity(length + 1), value(nullptr)
{
	this->value = new char[this->capacity];
	this->value[0] = '\0';
}

cstring::cstring(const char * value)
{
	this->length = std::strlen(value);
	this->capacity = this->length + 1;
	this->value = new char[this->capacity];
	strcpy(this->value, value);
}

tools::cstring::cstring(const cstring & other)
{
	this->length = other.get_length();
	this->capacity = this->length + 1;
	this->value = new char[this->capacity];
	strcpy(this->value, other.get_as_char_array());
}


cstring::~cstring()
{
	delete[] this->value;
}

unsigned int cstring::get_length() const
{
	return this->length;
}

unsigned int tools::cstring::get_capacity() const
{
	return this->capacity;
}

void tools::cstring::set_capacity(unsigned int length)
{
	if (!value)
	{
		this->value = new char[this->capacity];
		this->value[0] = '\0';
	}
	this->capacity = length + 1;
	char * buffer = new char[this->capacity];
	unsigned int min = this->get_length() < length ? this->get_length() : length;
	for (unsigned int i = 0; i <= min; i++)
	{
		buffer[i] = this->value[i];
	}
	delete[] this->value;
	this->value = buffer;
}

const char * tools::cstring::get_as_char_array() const
{
	return this->value;
}

cstring cstring::substring(unsigned int from, unsigned int to) const
{
	if (to < from)
	{
		throw std::logic_error("Cannot create a subcstring from staring position greater than ending position");
	}
	unsigned int capacity = to - from;
	cstring result(capacity);
	for (unsigned int i = from; i < to; i++)
	{
		result += (*this)[i];
	}
	return result;
}

int cstring::find_first_of(const cstring & c, unsigned int start_from) const
{
	int len = c.get_length();
	for (unsigned int i = start_from; i < this->length; ++i)
	{
		for (int j = 0; j < len; ++j)
		{
			if (c[j] == this->value[i])
			{
				return i;
			}
		}
	}
	return -1;
}

bool tools::cstring::contains(const char ch) const
{
	for (unsigned int i = 0; i < this->get_length(); i++)
	{
		if ((*this)[i] == ch)
		{
			return true;
		}
	}
	return false;
}

tools::Vector<cstring> cstring::split(const cstring & delim) const
{
	Vector<cstring> result;
	int from = 0;
	int to = 0;
	while (to < this->get_length())
	{
		to = this->find_first_of(delim, from);
		if (to < 0)
		{
			to = this->get_length();
		}
		result.add(this->substring(from, to));
		from = to + 1;
	}

	return result;
}

bool tools::cstring::ends_with(const cstring & something) const
{
	if (something.get_length() > this->get_length())
	{
		return false;
	}
	for (unsigned int i = 0; i < something.get_length(); i++)
	{
		if ((*this)[this->get_length() - 1 - i] != something[something.get_length() - 1 - i])
		{
			return false;
		}
	}
	return true;
}

bool cstring::starts_with(const char ch) const
{
	return this->value[0] == ch;
}

bool tools::cstring::to_int(int & out) const
{
	int result = 0;
	int multiplier = 1;
	size_t len = this->get_length();
	if (len == 0)
	{
		return false;
	}
	for (int i = len - 1; i > 0; --i)
	{
		if ((*this)[i] <= '9' && (*this)[i] >= '0')
		{
			result += ((*this)[i] - 48) * multiplier;
			multiplier *= 10;
		}
		else
		{
			return false;
		}
	}
	if ((*this)[0] == '-')
	{
		result *= -1;
	}
	else if ((*this)[0] <= '9' && (*this)[0] >= '0')
	{
		result += ((*this)[0] - 48) * multiplier;
		multiplier *= 10;
	}
	else
	{
		return false;
	}
	out = result;
	return true;
}

cstring tools::cstring::to_cstring(int num)
{
	int num_cpy = num;
	int len = 0;
	while (num_cpy > 0)
	{
		++len;
		num_cpy /= 10;
	}
	cstring result(len);
	while (num > 0)
	{
		result += (char)((num % 10) + 48);
		num /= 10;
	}
	return result;
}

bool tools::cstring::operator!=(const cstring & other) const
{
	return !(*this == other);
}

bool cstring::operator==(const cstring & other) const
{
	if (other.get_length() != this->get_length())
	{
		return false;
	}
	for (unsigned int i = 0; i < this->get_length(); i++)
	{
		if (other[i] != (*this)[i])
		{
			return false;
		}
	}
	return true;
}

cstring & cstring::operator+=(const cstring & other)
{
	unsigned int new_capacity = this->get_length() + other.get_length() + 1;
	char * newValue = new char[new_capacity];
	unsigned int index = 0;
	for (unsigned int i = 0; i < this->get_length(); ++i)
	{
		newValue[index] = this->value[i];
		index++;
	}

	for (unsigned int i = 0; i < other.get_length(); ++i)
	{
		newValue[index] = other[i];
		index++;
	}
	newValue[index] = '\0';

	delete[] this->value;
	this->value = newValue;
	this->capacity = new_capacity;
	this->length = new_capacity - 1;
	return *this;
}

// The idea here is to add one character very fast and efficient by initializing the object with greater capacity and then add char by char. Something like this:
// cstring str(big_capacity)
// for i=0 to big_capacity:
// str += some_char
cstring & cstring::operator+=(const char ch)
{
	if (this->capacity > this->length)
	{
		this->value[this->length] = ch;
		this->value[this->length + 1] = '\0';
		++this->length;
		return *this;
	}
	else
	{
		return *this += &ch;
	}

}

cstring & tools::cstring::operator=(const cstring & other)
{
	this->length = other.get_length();
	this->capacity = other.get_capacity();
	delete[] this->value;
	this->value = new char[this->capacity];
	strcpy(this->value, other.get_as_char_array());
	return *this;
}

char cstring::operator[](unsigned int index) const
{
	if (index < 0 || index >= this->length)
	{
		throw std::out_of_range("cstring index out of range");
	}
	return this->value[index];
}

char & cstring::operator[](unsigned int index)
{
	if (index < 0 || index >= this->length)
	{
		throw std::out_of_range("cstring index out of range");
	}
	return this->value[index];
}

std::istream & tools::operator>>(std::istream & in, cstring & obj)
{
	obj = "";
	char buffer[100];
	short i = 0;
	char c;
	in.get(c);
	while (c != ' ' && c != '\n' && c != '\t')
	{
		buffer[i++] = c;
		in.get(c);
		if (i == 99)
		{
			buffer[i] = '\0';
			obj += buffer;
			i = 0;
		}
	}
	if (i > 0)
	{
		buffer[i] = '\0';
		obj += buffer;
	}
	return in;
}

cstring tools::operator+(const cstring & a, const cstring & b)
{
	cstring c(a);
	c += b;
	return c;
}

std::ostream & tools::operator<<(std::ostream & os, const cstring & obj)
{
	const char * value = obj.get_as_char_array();
	os << (value);
	return os;
}
