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
#include <cstdarg>
using json_exceptions::bad_json_exception;
using json_exceptions::invalid_key_name_exception;
using namespace components;
using factory::ComponentFactory;

static const ArrayCreator theArrayCreator;

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

const Component & components::Array::get(const char * key) const
{
	int parsed;
	if (Number::tryParse(key, parsed))
	{
		return *this->values.getAt(parsed);
	}
	throw invalid_key_name_exception(key);
}

Component & components::Array::get(const char * key)
{
	int parsed;
	if (Number::tryParse(key, parsed))
	{
		return *this->values.getAt(parsed);
	}
	throw invalid_key_name_exception(key);
}

Indexable & components::Array::operator=(const Indexable & other)
{
	const Array & casted = dynamic_cast<const Array &>(other);
	return (*this = casted);
}

Indexable & components::Array::operator+=(const Indexable & other)
{
	const Array & casted = dynamic_cast<const Array&>(other);
	return (*this += casted);
}

void components::Array::update(const char * key, const char * json)
{
	int index;
	bool success = Number::tryParse(key, index);
	if (!success)
	{
		throw invalid_key_name_exception(key);
	}
	this->update(index, json);
}

void components::Array::update(int index, const char * json)
{
	Component * parsed = JSONParser::parseOne(json);
	if (parsed)
	{
		this->update(index, parsed);
	}
	else
	{
		try
		{
			Number * n = new Number(json);
			this->update(index, n);
		}
		catch (const std::exception&)
		{
			this->update(index, new String(json));
		}
	}
}

void components::Array::update(int index, double number)
{
	Number *n = new Number();
	this->update(index, n);
}

void components::Array::add(Component * item)
{
	this->values.add(item);
}

void components::Array::add(const char * json)
{
	Component * parsed = JSONParser::parseOne(json);
	if (parsed)
	{
		this->add(parsed);
	}
	else
	{
		try
		{
			Number * n = new Number(json);
			this->add(n);
		}
		catch (const std::exception& e)
		{
			this->add(new String(json));
		}

	}
}

void components::Array::add(const char * json1, const char * json2)
{
	this->add(json1);
	this->add(json2);
}

void components::Array::add(double number)
{
	this->values.add(new Number(number));
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
		if (*parsed == *this->values.getAt(i))
		{
			out = parsed;
			return true;
		}
	}
	delete parsed;
	return false;
}

Array & components::Array::operator=(const Array & other)
{
	if (this == &other)
	{
		return *this;
	}
	this->values.clear();
	for (size_t i = 0; i < other.size(); i++)
	{
		this->values.add(other.get(i).copy());
	}
	return *this;
}

Component & components::Array::operator=(const Component & other)
{
	const Array & casted = dynamic_cast<const Array&>(other);
	return *this = casted;
}

Component & components::Array::operator+=(const Component & other)
{
	const Array & casted = dynamic_cast<const Array &>(other);
	return (*this += casted);
}

Component * components::Array::copy() const
{
	Array * arr = new Array();
	for (size_t i = 0; i < this->values.count(); i++)
	{
		arr->add(this->values.getAt(i)->copy());
	}
	return arr;
}

Array & components::Array::operator+=(const Array & other)
{
	for (size_t i = 0; i < other.values.count(); i++)
	{
		this->values.add(other.values.getAt(i)->copy());
	}
	return *this;
}
Array & components::Array::operator-=(unsigned int index)
{
	this->values.removeAt(index);
	return *this;
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

bool components::Array::operator!=(const Component & other) const
{
	return !(*this == other);
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
	return true;
}

void components::Array::add(unsigned int items_count, ...)
{
	va_list args;
	va_start(args, items_count);
	for (size_t i = 0; i < items_count; i++)
	{
		const char * next_json = va_arg(args, const char *);
		if (next_json[0])
		{
			this->add(next_json);
		}
	}
	va_end(args);
}

void components::Array::update(const char * key, double number)
{
	int n;
	if (Number::tryParse(key, n))
	{
		this->update(n, number);
		return;
	}
	throw invalid_key_name_exception("Invalid key for array index");
}

void components::Array::update(const char * key, Component * new_value)
{
	int n;
	if (Number::tryParse(key, n))
	{
		this->update(n, new_value);
	}
	throw invalid_key_name_exception("Invalid key for array index");
}

void components::Array::update(int index, Component * new_value)
{
	this->values.setAt(index, new_value);
}
void components::Array::remove(const char * index)
{
	int n;
	if (Number::tryParse(index, n))
	{
		this->remove(n);
	}
	else
	{
		throw invalid_key_name_exception("Invalid key for array index");
	}

}
void components::Array::remove(int index)
{
	if (index >= 0)
	{
		this->values.removeAt(index);
	}
	else
	{
		throw std::out_of_range("Index out of rande");
	}
}

Indexable & components::Array::operator[](int index)
{
	return dynamic_cast<Indexable&>(this->get(index));
}
Indexable & components::Array::operator[](const char * key)
{
	return dynamic_cast<Indexable&>(this->get(key));
}
const Indexable & components::Array::operator[](const char * key) const
{
	return dynamic_cast<const Indexable&>(this->get(key));
}
const Indexable & components::Array::operator[](int index) const
{
	return dynamic_cast<const Indexable&>(this->get(index));
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
			if (complex == nullptr)
			{
				throw bad_json_exception("Unexpected or unknown token", line_number);
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
