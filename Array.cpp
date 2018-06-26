#include "Array.h"
#include "Number.h"
using components::Number;
#include <iostream>
#include <fstream>
#include <stdarg.h>
using std::cout;
#include "String.h"
#include "ComponentFactory.h"
#include "json_exceptions.hpp"
#include "JSONParser.h"
using interpreters::JSONParser;
using json_exceptions::bad_json_exception;

using factory::ComponentFactory;

components::Array::Array()
{

}

components::Array::Array(const Array & other)
{
	this->values = other.values;
}

components::Array::~Array()
{
}

const components::Component & components::Array::get(int index) const
{
	return *this->values.getAt(index);
}

Component & components::Array::get(int at)
{
	return *this->values.getAt(at);
}

void components::Array::add(Component * item)
{
	this->values.add(item);
}

void components::Array::add(const char * json)
{
	Vector<Token> tokens = Tokenizer::tokenize(json);
	Vector<Token>::Iterator i = tokens.createIterator();
	unsigned int line = 1;
	Component * parsed = ComponentFactory::getFactory().createNextFromTokens(i, line);
	if (parsed)
	{
		this->values.add(parsed);
	}
	else // treating it as a string
	{
		this->values.add(new String(json));
	}
}

void components::Array::add(double number)
{
	this->values.add(new Number(number));
}

void components::Array::update(unsigned int index, const char * json)
{
	Vector<Token> tokens = Tokenizer::tokenize(json);
	Vector<Token>::Iterator i = tokens.createIterator();
	unsigned int line = 1;
	Component * parsed = ComponentFactory::getFactory().createNextFromTokens(i, line);
	if (parsed)
	{
		this->values.setAt(index, parsed);
	}
	else // treating it as a string
	{
		this->values.setAt(index, new String(json));
	}
}

void components::Array::remove(unsigned int index)
{
	this->values.removeAt(index);
}

const unsigned int components::Array::size() const
{
	return this->values.count();
}

const bool components::Array::empty() const
{
	return this->size() == 0;
}

const bool components::Array::contains(const char * item, Component *& out) const
{
	Component * parsed;
	try
	{
		parsed = new Number(item);
	}
	catch (const std::exception&)
	{
		parsed = new String(item);
	}
	for (size_t i = 0; i < this->values.count(); i++)
	{
		if (*parsed == this->values.getAt(i))
		{
			out = parsed;
			return true;
		}
	}
	delete parsed;
	return false;
}

components::Component & components::Array::operator[](unsigned int index)
{
	return this->get(index);
}

const components::Component & components::Array::operator[](unsigned int index) const
{
	return this->get(index);
}
Array & components::Array::operator=(const Array & other)
{
	this->values = other.values;
	return *this;
}
Component & components::Array::operator=(Component * other)
{
	Array * arr = dynamic_cast<Array*>(other);
	if (arr)
	{
		return *this = *arr;
	}
	return *this;
}
Array & components::Array::operator+=(Array & other)
{
	for (size_t i = 0; i < other.values.count(); i++)
	{
		this->values.add(other.values.getAt(i));
	}
	return *this;
}
Array & components::Array::operator-=(unsigned int index)
{
	this->values.removeAt(index);
	return *this;
}
bool components::Array::operator==(const Component * other) const
{
	const Array * cast = dynamic_cast<const Array*>(other);
	if (cast)
	{
		return *this == *cast;
	}
	return false;
}

bool components::Array::operator==(const Component & other) const
{
	try
	{
		const Array & cast = dynamic_cast<const Array&>(other);
		return *this == cast;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

bool components::Array::operator==(const Array & other) const
{
	if (this->values.count() != other.values.count())
	{
		return false;
	}
	for (size_t i = 0; i < this->values.count(); i++)
	{
		if (!(this->values.getAt(i) == other.values.getAt(i)))
		{
			return false;
		}
	}
}
// override

void components::Array::print(std::ostream & out, unsigned short tab_index, bool pretty) const
{
	out << '[';
	if (this->values.count() > 0)
	{
		for (size_t i = 0; i < this->values.count() - 1; i++)
		{
			this->values.getAt(i)->print(out, tab_index, pretty);
			out << ", ";
		}

		this->values[this->values.count() - 1]->print(out, tab_index, pretty);
	}
	out << ']';
}
void components::Array::print(unsigned short tab_index, bool pretty) const
{
	this->print(cout, tab_index, pretty);
}

components::ArrayCreator::ArrayCreator()
	:ComponentCreator(Token(TokenNames::ArrayBegin, '['), Token(TokenNames::ArrayEnd, ']'))
{
}

components::Component * components::ArrayCreator::createComponent(Vector<Token>::Iterator & i, unsigned int & line_number) const
{
	Array * result = new Array();
	// in current pos of i should be token '['
	if (i->getName() != TokenNames::ArrayBegin)
	{
		throw bad_json_exception("Expected begin array token", line_number);
	}
	++i;
	while (i->getName() != TokenNames::ArrayEnd)
	{
		ComponentCreator::skipWhitespace(i, line_number);

		if (i->getName() == TokenNames::DoubleQuote)
		{
			++i;// skipping double quote
			String * s = new String(i->getValue());
			result->add(s);
			++i;
			if (i->getName() != TokenNames::DoubleQuote)
			{
				throw bad_json_exception("Expected double quote", line_number);
			}
			++i;// skipping double quote
		}
		else if (i->getName() == TokenNames::StringOrNumber)
		{
			try
			{
				Number * n = new Number(i->getValue());
				result->add(n);
				++i;
			}
			catch (const std::invalid_argument &)
			{
				throw bad_json_exception("Error converting to number", line_number);
			}
		}
		else
		{
			Component * complex = ComponentFactory::getFactory().createNextFromTokens(i, line_number);
			if (!complex)
			{
				throw bad_json_exception("Error parsing json object", line_number);
				return nullptr;
			}
			result->add(complex);
			++i;
		}
		ComponentCreator::skipWhitespace(i, line_number);
		if (i->getName() != Comma)
		{
			ComponentCreator::skipWhitespace(i, line_number);
			if (i->getName() != ArrayEnd)
			{
				throw bad_json_exception("Expected comma or array end token", line_number);
			}
			return result;
		}
		else
		{
			++i;
			ComponentCreator::skipWhitespace(i, line_number);
			if (i->getName() == ArrayEnd)
			{
				throw bad_json_exception("Unexpected token", line_number);
			}
		}
	}
	return result;
}
