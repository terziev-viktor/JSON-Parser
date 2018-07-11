#pragma once
#include "String.h"
static const components::creators::StringCreator theStringCreator;

components::String::String()
{

}

components::String::String(unsigned int capacity)
{
	this->value.set_capacity(capacity);
}

components::String::String(const cstring & str)
{
	this->value = str;
}

const char * components::String::get_value() const
{
	return this->value.get_as_char_array();
}

unsigned int components::String::get_length() const
{
	return this->value.get_length();
}

unsigned int components::String::get_capacity() const
{
	return this->value.get_capacity();
}

bool components::String::to_int(int & out) const
{
	return this->value.to_int(out);
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
	this->value = other.get_value();
	return *this;
}

components::String & components::String::operator+=(const String & other)
{
	this->value += other.get_value();
	return *this;
}

components::String & components::String::operator+=(const char ch)
{
	this->value += ch;
	return *this;
}

char components::String::operator[](unsigned int index) const
{
	return this->value[index];
}

char & components::String::operator[](unsigned int index)
{
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
