#pragma once
#include "String.h"
static const components::creators::StringCreator theStringCreator;

components::String::String() :length(0), capacity(1)
{
	this->value = new char[this->capacity];
	this->value[0] = '\0';
}

components::String::String(unsigned int capacity) :length(0), capacity(capacity + 1)
{
	this->value = new char[this->capacity];
	this->value[0] = '\0';
}

components::String::String(const char * value)
{
	this->length = strlen(value);
	this->capacity = this->length + 1;
	this->value = new char[this->capacity];
	strcpy(this->value, value);
}

components::String::String(const String & other)
{
	this->length = other.get_length();
	this->capacity = other.get_capacity();
	this->value = new char[this->capacity];
	strcpy(this->value, other.get_value());
}

components::String::~String()
{
	delete[] this->value;
}

const char * components::String::get_value() const
{
	return this->value;
}

unsigned int components::String::get_length() const
{
	return this->length;
}

unsigned int components::String::get_capacity() const
{
	return this->capacity;
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
		result += (*this)[i];
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
	while (to < this->get_length())
	{
		to = this->find_first(delim, from);
		if (to < 0)
		{
			to = this->get_length();
		}
		result.add(this->substring(from, to));
		from = to + 1;
	}

	return result;
}

bool components::String::to_int(int & out) const
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

bool components::String::starts_with(const char ch) const
{
	return this->value[0] == ch;
}

void components::String::print(std::ostream & out, bool pretty, unsigned int tab_index) const
{
	out << '"' << this->get_value() << '"';
}

bool components::String::equals(const Component & other) const
{
	try
	{
		const String & casted = dynamic_cast<const String &>(other);
		return (*this == casted);
	}
	catch (const std::exception&)
	{
		return false;
	}
}


components::Component * components::String::copy() const
{
	return new String(*this);
}

bool components::String::operator==(const String & other) const
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

components::String & components::String::operator=(const String & other)
{
	this->length = other.get_length();
	this->capacity = other.get_capacity();
	delete[] this->value;
	this->value = new char[this->capacity];
	strcpy(this->value, other.get_value());
	return *this;
}

const unsigned int components::String::size() const
{
	return this->get_length();
}

components::String & components::String::operator+=(const String & other)
{
	const size_t thisLen = this->get_length();
	const size_t otherLen = other.get_length();
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
		return (*this += &ch);
	}

}

char components::String::operator[](unsigned int index) const
{
	if (index >= this->get_length())
	{
		throw std::out_of_range("Index out of range");
	}
	return this->value[index];
}

char & components::String::operator[](unsigned int index)
{
	if (index >= this->get_length())
	{
		throw std::out_of_range("Index out of range");
	}
	return this->value[index];
}

cstring components::String::tell_type() const
{
	return "String";
}

components::String components::operator+(const String & a, const String & b)
{
	String c(a);
	c += b;
	return c;
}

std::ostream & components::operator<<(std::ostream & os, const String & obj)
{
	os << obj.get_value();
	return os;
}

components::Component * components::creators::StringCreator::createComponent(TokensSimulator & tokens, unsigned int & line_number) const
{
	return StringCreator::create_string(tokens, line_number);
}

components::String * components::creators::StringCreator::create_string(TokensSimulator & tokens, unsigned int & line)
{
	String * result = nullptr;
	if (tokens.get() != '"')
	{
		return nullptr;
	}
	tokens.next();
	int len = tokens.skip_until("\"");
	if (len == -1)
	{
		throw bad_json_exception("Expected double quote for string end", line);
	}
	result = new String(len);
	tokens.prev(len);
	result = new String(len);
	for (int i = 0; i < len; i++)
	{
		*result += tokens.get_next();
	}
	tokens.next();
	return result;
}
