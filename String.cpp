#include "String.h"
#include <string.h>
#include <iostream>
#include <fstream>

using std::cout;

components::String::String()
{
}

components::String::String(const char * value)
{
	size_t len = strlen(value);
	this->value = new char[len + 1];
	for (size_t i = 0; i <= len; i++)
	{
		this->value[i] = value[i];
	}
}


components::String::~String()
{
	if (value)
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
	return strlen(this->value);
}

const char components::String::charAt(int at) const
{
	return this->value[at];
}

void components::String::setValue(const char * value)
{
	if (this->value)
	{
		delete[] this->value;
	}
	size_t len = strlen(value);
	for (size_t i = 0; i < len; i++)
	{
		this->value[i] = value[i];
	}
}

void components::String::print() const
{
	print(cout);
}

void components::String::print(std::ostream & out) const
{
	out << this->value;
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

components::String & components::String::operator+=(const String & other)
{
	const size_t thisLen = this->getLen();
	const size_t otherLen = other.getLen();

	char * newValue = new char[thisLen + otherLen + 1];
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
	return *this;
}

components::StringCreator::StringCreator()
	:ComponentCreator("string")
{
}

components::Component * components::StringCreator::createComponent(std::ifstream & in) const
{
	return new String();
}
