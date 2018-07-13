#pragma once
#include "Composite.h"
#include "JSONParser.h"
using interpreters::JSONParser;
using namespace components;
#include <cstdarg>
#include "ComponentFactory.h"
using factory::ComponentFactory;

static const creators::CompositeCreator theCompositeCreator;

void components::Composite::print(std::ostream & out, bool pretty, unsigned int tab_index) const
{
	out << '{';
	if (this->count() == 0)
	{
		out << " }";
		return;
	}
	if (pretty)
	{
		out << '\n';
	}
	for (unsigned int i = 0; i < this->count() - 1; ++i)
	{
		for (unsigned short i = 0; i <= tab_index && pretty; i++)
		{
			out << '\t';
		}
		this->keys[i].print(out, pretty, tab_index);
		out << ':';
		this->values[i]->print(out, pretty, tab_index + 1);
		out << ',';
		if (pretty)
		{
			out << '\n';
		}
	}
	for (unsigned short i = 0; i <= tab_index && pretty; i++)
	{
		out << '\t';
	}
	this->keys[this->keys.count() - 1].print(out, pretty, tab_index);
	out << ':';
	this->values[this->values.count() - 1]->print(out, pretty, tab_index + 1);
	if (pretty)
	{
		out << '\n';
	}

	for (unsigned short i = 0; i < tab_index && pretty; i++)
	{
		out << '\t';
	}
	out << '}';
}

components::Composite::~Composite()
{
	this->values.delete_all_content();
}

const Vector<String> components::Composite::get_keys() const
{
	return this->keys;
}

const PointerContainer<Component> & components::Composite::get_values() const
{
	return this->values;
}

components::Composite::operator bool() const
{
	return !this->is_empty();
}

bool components::Composite::operator!() const
{
	return !(bool)(*this);
}

void components::Composite::add(unsigned int key_value_pairs_count, ...)
{
	va_list args;
	va_start(args, key_value_pairs_count);
	for (unsigned int i = 0; i < key_value_pairs_count; i++)
	{
		try
		{
			const char * key = va_arg(args, const char *);
			const char * value = va_arg(args, const char *);
			Component * parsed = JSONParser::parse(value);
			if (!parsed)
			{
				break;
			}
			this->keys.add(cstring(key));
			this->values.add(parsed);
		}
		catch (const std::exception&)
		{
			va_end(args);
			throw;
		}
	}
	va_end(args);
}

void components::Composite::add(const String & key, const Component & value)
{
	if (key.get_length() == 0)
	{
		throw invalid_key_name_exception(key.get_value());
	}
	this->keys.add(key);
	this->values.add(value.copy());
}

void components::Composite::update(const String & key, const Component & new_value)
{
	int ind = this->keys.index_of(key);
	if (ind == -1)
	{
		throw invalid_key_name_exception(key.get_value());
	}
	this->values.set_at(ind, new_value.copy(), true);
}

void components::Composite::swap(const String & key1, const String & key2)
{
	int index1, index2;
	index1 = this->keys.index_of(key1);
	index2 = this->keys.index_of(key2);
	if (index1 < 0 || index2 < 0)
	{
		throw invalid_key_name_exception("key/index");
	}

	Component * val1 = this->values[index1];
	Component * val2 = this->values[index2];
	this->values.set_at(index1, val2, false);
	this->values.set_at(index2, val1, false);
}

JSON & components::Composite::get(const String & key)
{
	Component & item = (*this)[key];
	JSON * casted = dynamic_cast<JSON *>(&item);
	if (!casted)
	{
		throw invalid_key_name_exception(key.get_value());
	}
	return *casted;
}

const JSON & components::Composite::get(const String & key) const
{
	const Component & item = (*this)[key];
	const JSON * casted = dynamic_cast<const JSON *>(&item);
	if (!casted)
	{
		throw invalid_key_name_exception(key.get_value());
	}
	return *casted;
}

void components::Composite::remove(const String & key)
{
	int ind = this->keys.index_of(key);
	if (ind == -1)
	{
		throw invalid_key_name_exception(key.get_value());
	}
	this->keys.remove_at(ind);
	this->values.delete_at(ind);
}

bool components::Composite::operator==(const Composite & other) const
{
	if (this->count() != other.count())
	{
		return false;
	}
	for (unsigned int i = 0; i < other.count(); i++)
	{
		if (!(this->values[i]->equals(*other.get_values()[i])))
		{
			return false;
		}
	}
	return true;
}

Composite & components::Composite::operator+=(const Composite & other)
{
	for (unsigned int i = 0; i < other.count(); i++)
	{
		this->add(other.get_keys()[i], *other.get_values()[i]);
	}
	return *this;
}

Composite & components::Composite::operator=(const Composite & other)
{
	if (this == &other)
	{
		return *this;
	}
	this->values = other.get_values();
	this->keys = other.get_keys();
	return *this;
}

Component & components::Composite::operator[](const String & key)
{
	int index = this->keys.index_of(key);
	if (index == -1)
	{
		throw invalid_key_name_exception(key.get_value());
	}
	Component * item = this->values[index];
	return *item;
}

const Component & components::Composite::operator[](const String & key) const
{
	int index = this->keys.index_of(key);
	if (index == -1)
	{
		throw invalid_key_name_exception(key.get_value());
	}
	const Component * item = this->values[index];
	return *item;
}

Component * components::Composite::copy() const
{
	Composite * c = new Composite();
	for (unsigned int i = 0; i < this->count(); i++)
	{
		c->add(this->get_keys()[i], *this->get_values()[i]);
	}
	return c;
}

unsigned int components::Composite::count() const
{
	return this->values.count();
}

int components::Composite::index_of(const Component & item) const
{
	for (unsigned int i = 0; i < this->values.count(); i++)
	{
		if (this->values[i]->equals(item))
		{
			return i;
		}
	}
	return -1;
}

bool components::Composite::equals(const Component & other) const
{
	try
	{
		const Composite & casted = dynamic_cast<const Composite&>(other);
		if (this->count() != casted.count())
		{
			return false;
		}
		for (unsigned int i = 0; i < this->count(); i++)
		{
			if (!(this->values[i]->equals(*casted.get_values()[i])))
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

cstring components::Composite::tell_type() const
{
	return "Composite";
}

bool components::Composite::is_empty() const
{
	return this->count() == 0;
}

void components::Composite::clear()
{
	this->values.delete_all_content();
	this->keys.clear();
}

Component * components::creators::CompositeCreator::createComponent(TokensSimulator & tokens, unsigned int & line_number) const
{
	return CompositeCreator::create_json(tokens, line_number);
}

Composite * components::creators::CompositeCreator::create_json(TokensSimulator & tokens, unsigned int & line_number)
{
	char c = tokens.get();
	if (c != '{')
	{
		return nullptr;
	}
	tokens.next();
	line_number += tokens.skip_whitespace();
	if (tokens.is_done())
	{
		throw bad_json_exception("Expected end of json token '}'", line_number);
	}
	Composite * result = new Composite();
	while (tokens.get() != '}')
	{
		line_number += tokens.skip_whitespace();
		if (tokens.is_done())
		{
			delete result;
			throw bad_json_exception("Expected end of json token '}'", line_number);
		}
		String * key = nullptr;
		Component * value = nullptr;
		try
		{
			key = StringCreator::create_string(tokens, line_number);
			line_number += tokens.skip_whitespace();
			if (tokens.get_next() != ':')
			{
				delete result;
				throw bad_json_exception("Expected key-value separator", line_number);
			}
			line_number += tokens.skip_whitespace();
			value = ComponentFactory::getFactory().createFromTokens(tokens, line_number);
		}
		catch (const std::exception& e)
		{
			if (key)
			{
				delete key;
			}
			if (value)
			{
				delete value;
			}
			delete result;
			throw e;
		}
		line_number += tokens.skip_whitespace();
		result->add(*key, *value);
		delete key;
		delete value;
		if (tokens.is_done())
		{
			delete result;
			throw bad_json_exception("Expected end of object token '{'.", line_number);
		}
		if (tokens.get() == ',')
		{
			int old = line_number;
			tokens.next();
			line_number += tokens.skip_whitespace();
			if (tokens.get() == '}')
			{
				delete result;
				throw bad_json_exception("Unexpected token ','", old);
			}
			continue;
		}
		else
		{
			line_number += tokens.skip_whitespace();
			if (tokens.is_done())
			{
				delete result;
				throw bad_json_exception("Expected end of object token '{'.", line_number);
			}
			if (tokens.get_next() != '}')
			{
				delete result;
				throw bad_json_exception("Expected end of json object token '}'", line_number);
			}
			return result;
		}
	}
	tokens.next();
	return result;
}
