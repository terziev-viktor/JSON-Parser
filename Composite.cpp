#pragma once
#include <iostream>
using std::cout;
using std::endl;
#include "Composite.h"
#include "JSONParser.h";
using interpreters::JSONParser;
using namespace components;
#include "json_exceptions.hpp"
#include <cstdarg>
using namespace json_exceptions;

static const CompositeCreator theCompositeCreator;

Composite::Composite()
{
}

components::Composite::Composite(const Composite & other)
{
	this->copyFrom(other);
}

components::Composite::Composite(const Indexable & other)
{
	const Composite & casted = dynamic_cast<const Composite &>(other);
	this->copyFrom(casted);
}

Composite::~Composite()
{
}

void Composite::print(unsigned short tab_index, bool pretty) const
{
	print(cout, tab_index, pretty);
}

void components::Composite::print(std::ostream & out, unsigned short tab_index, bool pretty) const
{
	out << '{';
	if (this->leafs.count() == 0)
	{
		out << " }";
		return;
	}
	if (pretty)
	{
		out << endl;
	}
	for (size_t i = 0; i < this->leafs.count() - 1; ++i)
	{
		for (unsigned short i = 0; i <= tab_index && pretty; i++)
		{
			out << '\t';
		}
		this->leafs.getAt(i).print(out, tab_index + 1, pretty);
		out << ',';
		if (pretty)
		{
			out << endl;
		}
	}
	for (unsigned short i = 0; i <= tab_index && pretty; i++)
	{
		out << '\t';
	}
	this->leafs.getAt(leafs.count() - 1).print(out, tab_index + 1, pretty);
	if (pretty)
	{
		out << endl;
	}

	for (unsigned short i = 0; i < tab_index && pretty; i++)
	{
		out << '\t';
	}
	out << '}';
}

Leaf & components::Composite::findLeaf(const char * key)
{
	unsigned int dummy;
	return this->findLeaf(key, dummy);
}

const Leaf & components::Composite::findLeaf(const char * key) const
{
	unsigned int dummy;
	return this->findLeaf(key, dummy);
}

Leaf & components::Composite::findLeaf(const char * key, unsigned int & out)
{
	for (unsigned int i = 0; i < this->leafs.count(); i++)
	{
		if (leafs[i] == key)
		{
			out = i;
			return leafs[i];
		}
	}
	throw invalid_key_name_exception(key);
}

const Leaf & components::Composite::findLeaf(const char * key, unsigned int & out) const
{
	for (unsigned int i = 0; i < this->leafs.count(); i++)
	{
		if (this->leafs[i] == key)
		{
			out = i;
			return leafs[i];
		}
	}
	throw invalid_key_name_exception(key);
}

void components::Composite::update(Leaf & l, const char * json)
{
	Component * parsed = JSONParser::parseOne(json);
	if (parsed)
	{
		l.setValue(parsed);
	}
	else
	{
		try
		{
			Number * n = new Number(json);
			l.setValue(n);
		}
		catch (const std::exception&)
		{
			l.setValue(new String(json));
		}
		
	}
}

bool components::Composite::leafExists(const char * key, unsigned int & out) const
{
	try
	{
		const Leaf & l = this->findLeaf(key, out);
		return true;
	}
	catch (const invalid_key_name_exception&)
	{
		return false;
	}
}

void components::Composite::copyFrom(const Composite & other)
{
	this->leafs = other.leafs;
}

const bool components::Composite::hasKey(const char * key) const
{
	unsigned int dummy;
	return this->leafExists(key, dummy);
}

void components::Composite::add(unsigned int key_value_pairs_count, ...)
{
	va_list args;
	va_start(args, key_value_pairs_count);
	for (unsigned int i = 0; i < key_value_pairs_count; i++)
	{
		const char * key = va_arg(args, const char *);
		const char * value = va_arg(args, const char *);
		this->add(key, value);
	}
	va_end(args);
}

void components::Composite::add(const char * key)
{
	throw json_exception("Invalid number of arguments for add method on composite object");
}

const Component & components::Composite::get(const char * name) const
{
	return *this->findLeaf(name).getValue();
}

Component & components::Composite::get(const char * name)
{
	return *this->findLeaf(name).getValue();
}

const Component & components::Composite::get(int index) const
{
	return *this->leafs.getAt(index).getValue();
}

Component & components::Composite::get(int index)
{
	return *this->leafs.getAt(index).getValue();
}

void components::Composite::add(const char * name, const char * json)
{
	Leaf * l = new Leaf();
	l->setName(name);
	Component * parsed = JSONParser::parseOne(json);

	if (parsed)
	{
		l->setValue(parsed);
	}
	else
	{
		try
		{
			Number * n = new Number(json);
			l->setValue(n);
		}
		catch (const std::exception&)
		{
			l->setValue(new String(json));
		}
	}
	this->add(*l);
}

void components::Composite::add(const Leaf & l)
{
	unsigned int dummy;
	if (this->leafExists(l.getName(), dummy))
	{
		throw invalid_key_name_exception(l.getName());
	}
	this->leafs.add(l);
}

void components::Composite::update(const char * key, const char * json)
{
	Leaf & l = this->findLeaf(key);
	this->update(l, json);
}

void components::Composite::update(int index, const char * json)
{
	if (index >= 0 && index < this->leafs.count())
	{
		Leaf & l = this->leafs.getAt(index);
		this->update(l, json);
	}
	throw invalid_key_name_exception("index");
}

void components::Composite::update(int index, double number)
{
	this->update(index, new Number(number));
}

void components::Composite::update(const char * key, double number)
{
	Leaf & l = this->findLeaf(key);
	l.setValue(new Number(number));
}

void components::Composite::update(const char * key, Component * new_value)
{
	Leaf & l = this->findLeaf(key);
	l.setValue(new_value);
}

void components::Composite::update(int index, Component * new_value)
{
	if (index >= 0 && index < this->leafs.count())
	{
		this->leafs.getAt(index).setValue(new_value);
	}
	throw invalid_key_name_exception("Invalid index for json key");
}

void components::Composite::remove(const char * name)
{
	unsigned int index;
	Leaf & l = this->findLeaf(name, index);
	this->remove(index);
}

void components::Composite::remove(int index)
{
	this->leafs.removeAt(index);
}

void components::Composite::swap(const char * keyA, const char * keyB)
{
	Component * tmp;
	Leaf & a = this->findLeaf(keyA);
	Leaf & b = this->findLeaf(keyB);
	tmp = a.getValue();
	a.value = b.getValue();
	b.value = tmp;
}

void components::Composite::swap(unsigned int index1, unsigned int index2)
{
	this->swap(this->leafs.getAt(index1).getName(), this->leafs.getAt(index2).getName());
}

bool components::Composite::operator==(const Composite & other) const
{
	return this->leafs == other.leafs;
}

Composite & components::Composite::operator+=(const Composite & other)
{
	this->leafs += other.leafs;
	return *this;
}

Composite & components::Composite::operator=(const Composite & other)
{
	if (this == &other)
	{
		return *this;
	}
	this->leafs = other.leafs;
	return *this;
}

Component & components::Composite::operator=(const Component & other)
{
	const Composite & c = dynamic_cast<const Composite&>(other);
	return (*this = c);
}

Component & components::Composite::operator+=(const Component & other)
{
	const Composite & casted = dynamic_cast<const Composite&>(other);
	return (*this += casted);
}

Component * components::Composite::copy() const
{
	Composite * c = new Composite();
	for (size_t i = 0; i < this->leafs.count(); i++)
	{
		Leaf *l = new Leaf();
		l->setName(this->leafs.getAt(i).getName());
		l->setValue(this->leafs.getAt(i).getValue()->copy());
		c->add(*l);
	}
	return c;
}

const unsigned int components::Composite::size() const
{
	return this->leafs.count();
}

bool components::Composite::operator==(const Component & other) const
{
	try
	{
		const Composite & casted = dynamic_cast<const Composite&>(other);
		if (this->leafs.count() != casted.leafs.count())
		{
			return false;
		}
		for (size_t i = 0; i < this->leafs.count(); i++)
		{
			if (!(this->leafs.getAt(i) == casted.leafs.getAt(i)))
			{
				return false;
			}
		}
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

bool components::Composite::operator!=(const Component & other) const
{
	return !(*this == other);
}

const Indexable & components::Composite::operator[](const char * key) const
{
	return dynamic_cast<const Indexable&>(this->get(key));
}

Indexable & components::Composite::operator[](const char * key)
{
	return dynamic_cast<Indexable&>(this->get(key));
}

const Indexable & components::Composite::operator[](int index) const
{
	if (index >= 0 && index < this->leafs.count())
	{
		return dynamic_cast<const Indexable&>(this->get(index));
	}
	throw std::invalid_argument("Invalid key");
}

Indexable & components::Composite::operator[](int index)
{
	if (index >= 0 && index < this->leafs.count())
	{
		return dynamic_cast<Indexable&>(this->get(index));
	}
	throw std::invalid_argument("Invalid key");
}

Indexable & components::Composite::operator=(const Indexable & other)
{
	const Composite & casted = dynamic_cast<const Composite &>(other);
	return *this = casted;
}

Indexable & components::Composite::operator+=(const Indexable & other)
{
	const Composite & casted = dynamic_cast<const Composite&>(other);
	return (*this += casted);
}

const bool components::Composite::contains(const char * key, Component * out) const
{
	unsigned int index;
	const bool yes = this->leafExists(key, index);
	if (yes)
	{
		out = this->get(index).copy();
		return true;
	}
	return false;

}

components::CompositeCreator::CompositeCreator()
	:ComponentCreator(Token(TokenNames::ObjectBegin, '{'), Token(TokenNames::ObjectEnd, '}'))
{
}

Component * components::CompositeCreator::createComponent(Vector<Token>::Iterator & i, unsigned int & line_number) const
{
	Composite * result = new Composite();

	if (i->getName() != TokenNames::ObjectBegin)
	{
		throw bad_json_exception("Expected begin of object token", line_number);
	}
	++i; // skipping '{'
	ComponentCreator::skipWhitespace(i, line_number);
	while (i->getName() != TokenNames::ObjectEnd)
	{
		ComponentCreator::skipWhitespace(i, line_number);
		if (i->getName() != TokenNames::DoubleQuote)
		{
			throw bad_json_exception("Expected double quote '\"'", line_number);
		}
		++i; // skipping "
		Leaf * keyValue = new Leaf();
		keyValue->setName(i->getValue());
		++i;
		if (i->getName() != TokenNames::DoubleQuote)
		{
			throw bad_json_exception("Expected double quote '\"'", line_number);
		}
		++i;
		ComponentCreator::skipWhitespace(i, line_number);
		if (i->getName() != TokenNames::KeyValSeparator)
		{
			throw bad_json_exception("Expected key-value separator ':'", line_number);
		}
		++i;
		ComponentCreator::skipWhitespace(i, line_number);
		if (i->getName() == TokenNames::DoubleQuote) // the value is a string
		{
			++i;
			keyValue->setValue(new String(i->getValue()));
			++i;
			if (i->getName() != TokenNames::DoubleQuote)
			{
				throw bad_json_exception("Expected double quote '\"'", line_number);
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
				throw bad_json_exception("Error converting number value", line_number);
			}
		}
		else
		{
			Component * l = ComponentFactory::getFactory().createNextFromTokens(i, line_number);
			if (!l)
			{
				throw bad_json_exception("Error parsing json object value", line_number);
			}
			keyValue->setValue(l);
			++i;
		}
		result->add(*keyValue);
		ComponentCreator::skipWhitespace(i, line_number);
		if (i->getName() != TokenNames::Comma)
		{
			ComponentCreator::skipWhitespace(i, line_number);
			if (i->getName() != TokenNames::ObjectEnd)
			{
				throw bad_json_exception("Expected object end token (or a comma)", line_number);
			}
			return result;
		}
		++i; // continue building object
	}
	return result;
}

Composite components::operator+(const Composite & left, const Composite & right)
{
	return Composite(left) += right;
}
