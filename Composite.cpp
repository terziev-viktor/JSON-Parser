#pragma once
#include <iostream>
using std::cout;
using std::endl;

#include "Composite.h"
using namespace components;

Composite::Composite()
{
}

Composite::~Composite()
{
}

void Composite::print() const
{
	print(cout);
}

void components::Composite::print(std::ostream & out) const
{
	out << "{\n";

	for (size_t i = 0; i < this->leafs.count(); ++i)
	{
		out << '\t';
		leafs.getAt(i)->print(out);
		out << endl;
	}

	out << "}\n";
}

const Leaf * Composite::getLeaf(int at) const
{
    return this->leafs.getAt(at);
}

Leaf * components::Composite::getLeaf(int n)
{
	return this->leafs.getAt(n);
}

const Leaf * components::Composite::getLeaf(const char * name) const
{
	for (size_t i = 0; i < this->leafs.count(); i++)
	{
		if (strcmp(name, this->leafs.getAt(i)->getName()) == 0)
		{
			return this->leafs.getAt(i);
		}
	}
	throw "Invalid name";
}

Leaf * components::Composite::getLeaf(const char * name)
{
	for (size_t i = 0; i < this->leafs.count(); i++)
	{
		if (strcmp(name, this->leafs.getAt(i)->getName()) == 0)
		{
			return this->leafs.getAt(i);
		}
	}
	throw "Invalid name";
}

void Composite::addLeaf(Leaf * child)
{
    this->leafs.add(child);
}

const Leaf * components::Composite::operator[](int n) const
{
	return this->getLeaf(n);
}

Leaf * components::Composite::operator[](int n)
{
	return this->getLeaf(n);
}

const Leaf * components::Composite::operator[](const char * name) const
{
	return this->getLeaf(name);
}

Leaf * components::Composite::operator[](const char * name)
{
	return this->getLeaf(name);
}

components::CompositeCreator::CompositeCreator()
	:ComponentCreator(Token(TokenNames::ObjectBegin, '{'), Token(TokenNames::ObjectEnd, '}'))
{
}

Component * components::CompositeCreator::createComponent(Vector<Token>::Iterator & i) const
{
	Composite * result = new Composite();

	if (i->getName() != TokenNames::ObjectBegin)
	{
		cout << " Expected '{'" << endl;
		return result;
	}
	++i; // skipping '{'
	while (i->getName() != TokenNames::ObjectEnd)
	{
		while (i->getName() == TokenNames::Spacebar || i->getName() == TokenNames::Tab || i->getName() == TokenNames::NewLine) { ++i; } // skipping whipespace

		if (i->getName() != TokenNames::DoubleQuote)
		{
			cout << "Expected '\"'" << endl;
			return result;
		}
		++i; // skipping "
		Leaf * keyValue = new Leaf();
		keyValue->setName(i->getValue());
		++i;
		if (i->getName() != TokenNames::DoubleQuote)
		{
			cout << "Expected '\"'" << endl;
			delete keyValue;
			return result;
		}
		++i;
		while (i->getName() == TokenNames::Spacebar || i->getName() == TokenNames::Tab || i->getName() == TokenNames::NewLine) { ++i; } // skipping whipespace

		if (i->getName() != TokenNames::KeyValSeparator)
		{
			cout << "Expected key value separator ':'" << endl;
			return result;
		}
		++i;
		while (i->getName() == TokenNames::Spacebar || i->getName() == TokenNames::Tab || i->getName() == TokenNames::NewLine) { ++i; } // skipping whipespace
		if (i->getName() == TokenNames::DoubleQuote) // the value is a string
		{
			++i;
			keyValue->setValue(new String(i->getValue()));
			++i;
			if (i->getName() != TokenNames::DoubleQuote)
			{
				cout << "Expected '\"'" << endl;
				delete keyValue;
				return result;
			}
			++i;
		}
		else if (i->getName() == TokenNames::StringOrNumber)
		{
			try
			{
				keyValue->setValue(new Number(i->getValue()));
				++i;
			}
			catch (const std::invalid_argument& e)
			{
				cout << "Not a number " << endl;
				delete keyValue;
				return result;
			}
		}
		else
		{
			Component * l = ComponentFactory::getFactory().createNextFromTokens(i);
			if (!l)
			{
				cout << "Error" << endl;
				delete keyValue;
				return result;
			}
			keyValue->setValue(l);
			++i;
		}
		result->addLeaf(keyValue);

		while (i->getName() == TokenNames::Spacebar || i->getName() == TokenNames::Tab || i->getName() == TokenNames::Comma || i->getName() == NewLine) { ++i; } // skipping whipespace

	}
	return result;
}
