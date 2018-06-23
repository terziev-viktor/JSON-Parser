#include "Array.h"
#include "Number.h"
using components::Number;
#include <iostream>
#include <fstream>
#include <stdarg.h>
using std::cout;
#include "String.h"
#include "ComponentFactory.h"
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

components::Component * components::Array::operator[](int index)
{
	return this->values.getAt(index);
}

const components::Component * components::Array::operator[](int index) const
{
	return this->values.getAt(index);
}

// override

void components::Array::print(std::ostream & out) const
{
	out << '[';
	if (this->values.count() > 0)
	{
		for (size_t i = 0; i < this->values.count() - 1; i++)
		{
			this->values.getAt(i)->print();
			out << ", ";
		}

		this->values.getAt(this->values.count() - 1)->print();
	}

	out << ']';
}
void components::Array::print() const
{
	this->print(cout);
}

components::ArrayCreator::ArrayCreator()
	:ComponentCreator(Token(TokenNames::ArrayBegin, '['), Token(TokenNames::ArrayEnd, ']'))
{
}

components::Component * components::ArrayCreator::createComponent(Vector<Token>::Iterator & i) const
{
	Array * result = new Array();
	// in current pos of i should be token '['
	if (i->getName() != TokenNames::ArrayBegin)
	{
		cout << "Expected begin array token" << endl;
		return nullptr;
	}
	++i;
	while (i->getName() != TokenNames::ArrayEnd)
	{
		while (!i.isDone() && (i->getName() == TokenNames::Tab || i->getName() == TokenNames::Spacebar)) { ++i; }

		if (i->getName() == TokenNames::DoubleQuote)
		{
			++i;// skipping double quote
			String * s = new String(i->getValue());
			result->add(s);
			++i;
			if (i->getName() != TokenNames::DoubleQuote)
			{
				cout << "Expected double quote" << endl;
				return result;
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
				cout << "Not a number" << endl;
				return result;
			}
		}
		else
		{
			List<Component> * l = ComponentFactory::getFactory().createFromTokens(i);
			if (!l)
			{
				cout << "Error on line n" << endl;
				return result;
			}
			result->add(l->getAt(0));
			++i;
		}
		while (!i.isDone() && (i->getName() == TokenNames::Tab || i->getName() == TokenNames::Spacebar || i->getName() == TokenNames::Comma)) { ++i; }
	}
	return result;
}
