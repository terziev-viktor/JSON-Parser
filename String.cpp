#include "String.h"
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

components::String::String(size_t capacity)
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
	this->capacity = this->length + 1;
	this->value = new char[this->capacity];
	for (size_t i = 0; i <= this->length; i++)
	{
		this->value[i] = value[i];
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

const size_t components::String::getLen() const
{
	return this->length;
}

components::String components::String::substring(size_t from, size_t to) const
{
	if (to < from)
	{
		throw std::logic_error("to cannot be before from");
	}
	size_t capacity = to - from;
	String result(capacity);
	for (size_t i = from; i < to; i++)
	{
		result += this->charAt(i);
	}
	return result;
}

const int components::String::find_first(const char c, size_t start_from) const
{
	for (int i = start_from; i < this->length; ++i)
	{
		if (this->value[i] == c)
		{
			return i;
		}
	}
	return -1;
}

const int components::String::find_first_of(const char * c, size_t start_from) const
{
	size_t len = strlen(c);
	for (int i = start_from; i < this->length; ++i)
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

const char components::String::charAt(unsigned int at) const
{
	if (at < 0 || at >= this->length)
	{
		throw std::out_of_range("Index out of range");
	}
	return this->value[at];
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

void components::String::setValue(const char c)
{
	if (this->value)
	{
		delete[] this->value;
	}
	this->value = new char[2];
	this->length = 1;
	this->capacity = 2;
	this->value[0] = c;
	this->value[1] = '\0';
}

const bool components::String::startsWith(const char ch) const
{
	return this->value[0] == ch;
}

void components::String::print(unsigned short tab_index) const
{
	print(cout);
}

void components::String::print(std::ostream & out, unsigned short tab_index) const
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
	this->setValue(c);
	return *this;
}

components::String & components::String::operator=(const String & other)
{
	this->setValue(other.getValue());
	return *this;
}

bool components::String::operator==(const String & other) const
{
	const size_t thisLen = this->getLen();
	const size_t otherLen = other.getLen();

	if (thisLen != otherLen)
	{
		return false;
	}
	const char * otherVal = other.getValue();

	for (size_t i = 0; i < thisLen; i++)
	{
		if (this->value[i] != otherVal[i])
		{
			return false;
		}
	}
	return true;
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

components::String & components::String::operator+=(const String & other)
{
	const size_t thisLen = this->getLen();
	const size_t otherLen = other.getLen();

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
		newValue[index] = other.value[i];
		index++;
	}
	newValue[index] = '\0';

	delete[] this->value;
	this->value = newValue;
	this->capacity = new_capacity;
	this->length = new_capacity - 1;
	return *this;
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

components::String & components::String::operator+=(const char ch)
{
	if (this->capacity > this->length)
	{
		this->value[this->length] = ch;
		this->value[this->length + 1] = '\0';
		++this->length;
	}
	else
	{
		char * new_buffer = new char[this->capacity + 1];
		this->capacity += 1;
		for (size_t i = 0; i < this->length; i++)
		{
			new_buffer[i] = this->value[i];
		}
		new_buffer[this->length] = ch;
		new_buffer[this->length + 1] = '\0';
		++this->length;
	}
	return *this;
}

const components::Component * components::String::operator[](unsigned int index) const
{
	return new String(this->charAt(index));
}

components::Component * components::String::operator[](unsigned int index)
{
	if (index < 0 || index >= this->length)
	{
		throw std::out_of_range("Index out of range");
	}
	return new String(this->value[index]);
}

std::ostream & components::operator<<(std::ostream & os, const String & obj)
{
	os << obj.getValue();
	return os;
}
