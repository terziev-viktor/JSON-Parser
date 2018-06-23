#include "Array.h"
#include "Number.h"
using components::Number;
#include <iostream>
#include <fstream>
#include <stdarg.h>
using std::cout;
#include "String.h"
#include "ComponentFactory.h"
#include "bad_json_exception.hpp"
using json_exceptions::bad_json_exception;

using factory::ComponentFactory;

components::Array::Array()
{

}

components::Array::~Array()
{
}

const components::Component * components::Array::get(int at) const
{
	return this->values.getAt(at);
}

void components::Array::add(components::Component * value)
{
	this->values.add(value);
}

const unsigned int components::Array::size() const
{
	return this->values.count();
}

components::Component * components::Array::operator[](unsigned int index)
{
	return this->values.getAt(index);
}

const components::Component * components::Array::operator[](unsigned int index) const
{
	return this->values.getAt(index);
}
// override

void components::Array::print(std::ostream & out, unsigned short tab_index) const
{
	out << '[';
	if (this->values.count() > 0)
	{
		for (size_t i = 0; i < this->values.count() - 1; i++)
		{
			this->values.getAt(i)->print(out, tab_index);
			out << ", ";
		}

		this->values.getAt(this->values.count() - 1)->print(out, tab_index);
	}
	out << ']';
}
void components::Array::print(unsigned short tab_index) const
{
	this->print(cout, tab_index);
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
		this->skipWhitespace(i, line_number);
		
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
			}
			result->add(complex);
			++i;
		}
		this->skipWhitespace(i, line_number);
		if (i->getName() != Comma && i->getName() != ArrayEnd)
		{
			throw bad_json_exception("Expected comma or array end token", line_number);
		}
		if (i->getName() == TokenNames::Comma && (++i)->getName() == TokenNames::ArrayEnd)
		{
			throw bad_json_exception("Unexpected token ','", line_number);
		}
	}
	return result;
}
