#pragma once
#include "Array.h"
#include <fstream>
using std::cout;
#include "ComponentFactory.h"
#include <cstdarg>
#include "JSONParser.h"
using interpreters::JSONParser;
using namespace components;
using factory::ComponentFactory;
using creators::ArrayCreator;

static const creators::ArrayCreator theArrayCreator;

components::Array::~Array()
{
	this->values.delete_all_content();
}

bool components::Array::is_empty() const
{
	return this->count() == 0;
}

unsigned int components::Array::count() const
{
	return this->values.count();
}

void components::Array::clear()
{
	this->values.clear();
}

int components::Array::index_of(const Component & item) const
{
	for (unsigned int i = 0; i < this->values.count(); i++)
	{
		if (item.equals(*this->values[i]))
		{
			return i;
		}
	}
	return -1;
}

Array & components::Array::operator=(const Array & other)
{
	if (this == &other)
	{
		return *this;
	}
	this->values.delete_all_content();
	for (unsigned int i = 0; i < other.count(); i++)
	{
		this->values.add(other[i].copy());
	}
	return *this;
}

Component * components::Array::copy() const
{
	Array * arr = new Array();
	for (size_t i = 0; i < this->values.count(); i++)
	{
		arr->add(*this->values[i]);
	}
	return arr;
}

Array & components::Array::operator+=(const Array & other)
{
	for (unsigned int i = 0; i < other.values.count(); i++)
	{
		this->values.add(other.values[i]->copy());
	}
	return *this;
}

Array & components::Array::operator-=(unsigned int index)
{
	this->values.set_at(index, nullptr, true);
	return *this;
}

bool components::Array::operator==(const Array & other) const
{
	if (this->values.count() != other.values.count())
	{
		return false;
	}
	for (unsigned int i = 0; i < this->values.count(); i++)
	{
		if (!(this->values[i]->equals(*other.values[i])))
		{
			return false;
		}
	}
	return true;
}

bool components::Array::operator!=(const Array & other) const
{
	return !(*this == other);
}

Component & components::Array::operator[](unsigned int index)
{
	return *this->values[index];
}

const Component & components::Array::operator[](unsigned int index) const
{
	return *this->values[index];
}

components::Array::operator bool() const
{
	return !this->is_empty();
}

bool components::Array::operator!() const
{
	return !(bool)(*this);
}

JSON & components::Array::get(const String & str)
{
	int index;
	if (str.to_int(index))
	{
		Component * item = this->values[index];
		JSON * casted = dynamic_cast<JSON *>(item);
		if (!casted)
		{
			throw invalid_key_name_exception(str.get_value());
		}
		return *casted;
	}
	throw invalid_key_name_exception(str.get_value());
}

const JSON & components::Array::get(const String & str) const
{
	int index;
	if (str.to_int(index))
	{
		const Component * item = this->values[index];
		const JSON * casted = dynamic_cast<const JSON *>(item);
		if (!casted)
		{
			throw invalid_key_name_exception(str.get_value());
		}
		return *casted;
	}
	throw invalid_key_name_exception(str.get_value());
}

void components::Array::add(unsigned int items_count, ...)
{
	JSONParser parser;
	va_list args;
	va_start(args, items_count);
	for (size_t i = 0; i < items_count; i++)
	{
		try
		{
			const char * next_json_str = va_arg(args, const char *);
			Component * next_json = parser.parse(next_json_str);
			if (!next_json)
			{
				
			}
			this->add(*next_json);
			delete next_json;
		}
		catch (const std::exception&)
		{
			va_end(args);
			throw json_exception("Invalid json arguments for add method of Array");
		}
	}
	va_end(args);
}

void components::Array::update(const String& str, const Component & new_value)
{
	int index;
	if (!str.to_int(index))
	{
		throw invalid_key_name_exception(str.get_value());
	}
	this->values.set_at(index, new_value.copy(), true);
}

void components::Array::remove(const String& str)
{
	int index;
	if (!str.to_int(index))
	{
		throw invalid_key_name_exception(str.get_value());
	}
	this->values.delete_at(index);
}

void components::Array::swap(const String& str1, const String& str2)
{
	int index1, index2;
	if (!str1.to_int(index1))
	{
		throw invalid_key_name_exception(str1.get_value());
	}
	if (!str2.to_int(index2))
	{
		throw invalid_key_name_exception(str2.get_value());
	}
	Component * a = this->values[index1];
	Component * b = this->values[index2];
	this->values.set_at(index1, b, false);
	this->values.set_at(index2, a, false);
}

void components::Array::add(const Component & item)
{
	this->values.add(item.copy());
}

void components::Array::print(std::ostream & out, bool pretty, unsigned int tab_index) const
{
	out << '[';
	if (this->values.count() > 0)
	{
		for (unsigned int i = 0; i < this->values.count() - 1; i++)
		{
			this->values[i]->print(out, pretty, tab_index);
			out << ", ";
		}
		this->values[this->values.count() - 1]->print(out, pretty, tab_index);
	}
	out << ']';
	
}

bool components::Array::equals(const Component & other) const
{
	return false;
}

cstring components::Array::tell_type() const
{
	return "Array";
}

Component * components::creators::ArrayCreator::createComponent(TokensSimulator & tokens, unsigned int & line_number) const
{
	return ArrayCreator::create_array(tokens, line_number);
}

Array * components::creators::ArrayCreator::create_array(TokensSimulator & tokens, unsigned int & line_number)
{
	if (tokens.get() != '[')
	{
		return nullptr;
	}
	tokens.next();
	line_number += tokens.skip_whitespace();
	if (tokens.is_done())
	{
		throw bad_json_exception("Unexpected end of file/string", line_number);
	}
	Array * result = new Array();
	while (tokens.get() != ']')
	{
		line_number += tokens.skip_whitespace();
		if (tokens.is_done())
		{
			delete result;
			throw bad_json_exception("Unexpected end of file/string", line_number);
		}
		Component * item;
		try
		{
			item = ComponentFactory::getFactory().createFromTokens(tokens, line_number);
		}
		catch (const std::exception&)
		{
			delete result;
			throw;
		}
		result->add(*item);
		delete item;
		line_number += tokens.skip_whitespace();
		if (tokens.is_done())
		{
			delete result;
			throw bad_json_exception("Unexpected end of file or object", line_number);
		}
		if (tokens.get() == ',')
		{
			int old = line_number;
			tokens.next();
			line_number += tokens.skip_whitespace();
			if (tokens.get() == ']')
			{
				delete result;
				throw bad_json_exception("Unexpected comma", old);
			}
			else
			{
				continue;
			}
		}
		else
		{
			line_number += tokens.skip_whitespace();
			if (tokens.get_next() != ']')
			{
				delete result;
				throw bad_json_exception("Expected end of array token ']'", line_number);
			}
			return result;
		}
		tokens.next();
		line_number += tokens.skip_whitespace();
	}
	tokens.next();
	return result;
}

