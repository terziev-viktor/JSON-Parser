#include "String.h"
#include "Number.h"
#include <string.h>
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
components::String::String()
{
	this->value = nullptr;
	this->length = 0;
	this->capacity = 0;
}

components::String::String(unsigned int capacity)
{
	this->capacity = capacity + 1;
	this->length = 0;
	this->value = new char[this->capacity];
	this->value[0] = '\0';
}

components::String::String(const String & other)
{
	this->length = other.getLen();
	this->capacity = this->length + 1;
	this->value = new char[this->capacity];
	for (size_t i = 0; i < this->length; i++)
	{
		this->value[i] = other.value[i];
	}
	this->value[this->length] = '\0';
}

components::String::String(const string & other)
{
	this->length = other.length();
	this->capacity = other.length() + 1;
	this->value = new char[this->capacity];
	strcpy_s(this->value, this->capacity, other.c_str());
}

components::String::String(const char * value)
{
	this->length = strlen(value);
	if (this->length == 0)
	{
		this->capacity = 0;
		this->value = nullptr;
	}
	else
	{
		this->capacity = this->length + 1;
		this->value = new char[this->capacity];
		for (size_t i = 0; i <= this->length; i++)
		{
			this->value[i] = value[i];
		}
	}
}


components::String::~String()
{
	if (this->value)
	{
		delete[] this->value;
	}
}

const char * components::String::getValue() const
{
	return this->value;
}

const unsigned int components::String::getLen() const
{
	return this->length;
}

components::String components::String::substring(unsigned int from, unsigned int to) const
{
	if (to < from)
	{
		throw std::logic_error("Cannot create a substring from staring position greater than ending position");
	}
	unsigned int capacity = to - from;
	String result(capacity);
	for (unsigned int i = from; i < to; i++)
	{
		result += this->charAt(i);
	}
	return result;
}

const int components::String::find_first(const char c, unsigned int start_from) const
{
	char str[2];
	str[0] = c;
	str[1] = '\0';
	return this->find_first_of(str, start_from);
}

const int components::String::find_first_of(const char * c, unsigned int start_from) const
{
	size_t len = strlen(c);
	for (unsigned int i = start_from; i < this->length; ++i)
	{
		for (size_t j = 0; j < len; ++j)
		{
			if (c[j] == this->value[i])
			{
				return i;
			}
		}
	}
	return -1;
}

tools::Vector<components::String> components::String::split(char delim) const
{
	Vector<String> result;
	int from = 0;
	int to = 0;
	while (to < this->getLen())
	{
		to = this->find_first(delim, from);
		if (to < 0)
		{
			to = this->getLen();
		}
		result.add(this->substring(from, to));
		from = to + 1;
	}
	
	return result;
}

const char components::String::charAt(unsigned int at) const
{
	if (at < 0 || at >= this->length)
	{
		throw std::out_of_range("String index out of range");
	}
	return this->value[at];
}

void components::String::setValue(const char c)
{
	char str[2];
	str[0] = c;
	str[1] = '\0';
	this->setValue(str);
}

void components::String::setValue(const char * value)
{
	if (this->value)
	{
		delete[] this->value;
	}
	this->length = strlen(value);
	this->capacity = this->length + 1;
	this->value = new char[this->capacity];
	for (size_t i = 0; i <= this->length; i++)
	{
		this->value[i] = value[i];
	}
}

const bool components::String::startsWith(const char ch) const
{
	return this->value[0] == ch;
}

void components::String::print(unsigned short tab_index, bool pretty) const
{
	print(cout, tab_index, pretty);
}

void components::String::print(std::ostream & out, unsigned short tab_index, bool pretty) const
{
	out << "\"" << this->value << "\"";
}

components::String & components::String::operator=(const char * other)
{
	this->setValue(other);
	return *this;
}

components::String & components::String::operator=(const char c)
{
	return *this = &c;
}

components::String & components::String::operator=(const String & other)
{
	return *this = other.getValue();
}

components::String & components::String::operator=(const string & other)
{
	*this = other.c_str();
	return *this;
}

components::Component * components::String::copy() const
{
	return new String(*this);
}

bool components::String::operator==(const Component & other) const
{
	try
	{
		const String & casted = dynamic_cast<const String&>(other);
		return *this == casted;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

bool components::String::operator!=(const Component & other) const
{
	return !(*this == other);
}

components::Component & components::String::operator=(const Component & other)
{
	const String & str = dynamic_cast<const String&>(other);
	return (*this = str.getValue());
}

components::Component & components::String::operator+=(const Component & other)
{
	const String & casted = dynamic_cast<const String&>(other);
	return (*this += casted);
}

bool components::String::operator==(const String & other) const
{
	return *this == other.getValue();
}

bool components::String::operator==(const char c) const
{
	char str[2];
	str[0] = c;
	str[1] = '\0';
	return *this == str;
}

bool components::String::operator==(const char * other) const
{
	if (strlen(other) != this->getLen())
	{
		return false;
	}
	for (size_t i = 0; i < this->getLen(); i++)
	{
		if (other[i] != this->getValue()[i])
		{
			return false;
		}
	}
	return true;
}

const unsigned int components::String::size() const
{
	return this->getLen();
}

components::String & components::String::operator+=(const String & other)
{
	return (*this += other.getValue());
}

components::String & components::String::operator+=(const char * other)
{
	const size_t thisLen = this->getLen();
	const size_t otherLen = strlen(other);
	size_t new_capacity = thisLen + otherLen + 1;
	char * newValue = new char[new_capacity];
	size_t index = 0;
	for (size_t i = 0; i < thisLen; i++)
	{
		newValue[index] = this->value[i];
		index++;
	}

	for (size_t i = 0; i < otherLen; i++)
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
// String str(big_capacity)
// for i=0 to big_capacity:
// str += some_char
components::String & components::String::operator+=(const char ch)
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

const char components::String::operator[](unsigned int index) const
{
	return this->charAt(index);
}

char components::String::operator[](unsigned int index)
{
	return this->charAt(index);
}

components::String components::operator+(const String & a, const String & b)
{
	String c(a);
	c += b;
	return c;
}

std::ostream & components::operator<<(std::ostream & os, const String & obj)
{
	os << obj.getValue();
	return os;
}
