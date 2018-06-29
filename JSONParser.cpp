#include "JSONParser.h"
#include <fstream>
#include "json_exceptions.hpp"
using namespace json_exceptions;
using std::ifstream;
using namespace interpreters;

JSONParser::JSONParser()
{
	this->list = nullptr;
	this->fileLoaded = false;
}

JSONParser::~JSONParser()
{
	delete this->list;
}

Indexable * interpreters::JSONParser::findAll(const char * key, const Indexable & obj)
{
	return nullptr;
}

const Component * JSONParser::get(unsigned int index) const
{
	return this->list->getAt(index);
}

Component * interpreters::JSONParser::get(unsigned int index)
{
	return this->list->getAt(index);
}

const unsigned int interpreters::JSONParser::getParsedCount() const
{
	if (this->list)
	{
		return this->list->count();
	}
	return 0;
}

const Indexable & interpreters::JSONParser::operator[](unsigned int index) const
{
	if (index < 0 || index >= this->getParsedCount())
	{
		throw json_exception("Invalid index");
	}
	return dynamic_cast<const Indexable&>(*this->get(index));
}

Indexable & interpreters::JSONParser::operator[](unsigned int index)
{
	if (index < 0 || index >= this->getParsedCount())
	{
		throw json_exception("Invalid index");
	}
	return dynamic_cast<Indexable&>(*this->get(index));
}

void JSONParser::add(Component * component)
{
	this->list->add(component);
}

void JSONParser::print() const
{
	for (unsigned int i = 0; i < this->list->count(); i++)
	{
		this->list->getAt(i)->print();
	}
}

const string & interpreters::JSONParser::getFile() const
{
	return this->file;
}

bool interpreters::JSONParser::fileExists(const char * path) const
{
	std::ifstream f;
	f.open(path);
	return f.good();
}

bool JSONParser::parse(const std::string & json)
{
	Vector<Token> tokens = Tokenizer::tokenize(json);
	Vector<Token>::Iterator i = tokens.createIterator();
	this->list = ComponentFactory::getFactory().createFromTokens(i);
	return this->list->count() > 0;
}

bool JSONParser::parse(const char * json)
{
	std::string str(json);
	return this->parse(str);
}

bool interpreters::JSONParser::parse()
{
	if (!this->fileLoaded)
	{
		return false;
	}
	return this->parse(this->file);
}

Component * interpreters::JSONParser::parseOne(const char * json)
{
	Vector<Token> tokens = Tokenizer::tokenize(json);
	Vector<Token>::Iterator i = tokens.createIterator();
	unsigned int line = 1;
	ComponentCreator::skipWhitespace(i, line);
	Component * p = ComponentFactory::getFactory().createNextFromTokens(i, line);
	if (p)
	{
		++i;
		ComponentCreator::skipWhitespace(i, line);
		if (!i.isDone())
		{
			throw bad_json_exception("End of string/file expected", line);
		}
		return p;
	}
	return nullptr;
}

bool interpreters::JSONParser::load(const char * path)
{
	ifstream in;
	char buffer[1025];
	in.open(path);
	if (!in)
	{
		in.close();
		return false;
	}
	while (in)
	{
		in.getline(buffer, 1024);
		if (in.gcount() > 0)
		{
			buffer[in.gcount() - 1] = '\n';
			buffer[in.gcount()] = '\0';
			this->file += buffer;
		}
	}
	this->fileLoaded = true;
	return true;
}

bool interpreters::JSONParser::save(const char * path, bool overrideFile, bool pretty) const
{
	for (size_t i = 0; i < this->list->count(); i++)
	{
		bool success = this->save(this->list->getAt(i), path, false, pretty);
		if (!success)
		{
			return false;
		}
	}
	return true;
}

bool interpreters::JSONParser::save(const Component * item, const char * path, bool overrideFile, bool pretty) const
{
	size_t len = strlen(path);
	if (path[len - 1] != 'n' || path[len - 2] != 'o' || path[len - 3] != 's' || path[len - 4] != 'j' || path[len - 5] != '.')
	{
		throw json_exception("path must be .json file");
		return false;
	}
	std::ofstream jsonFile;
	if (overrideFile)
	{
		jsonFile.open(path);
	}
	else
	{
		jsonFile.open(path, std::ios::app);
	}

	if (!jsonFile)
	{
		throw json_exception("Could not open file");
		return false;
	}
	item->print(jsonFile, 0, pretty);
	jsonFile.close();
	return true;
}

//Array * interpreters::JSONParser::findAll(const char * key)
//{
//	Array * arr = new Array();
//	for (size_t i = 0; i < this->list->count(); i++)
//	{
//		Composite * c = this->getAsJsonObject(i);
//		if (c && c->hasKey(key))
//		{
//			arr->add(c->get(key));
//		}
//		else
//		{
//			Array * casted = this->getAsJsonArray(i);
//			Component * out;
//			bool contains = casted->contains(key, out);
//			if (casted && contains)
//			{
//				arr->add(out);
//			}
//		}
//	}
//	return arr;
//}

bool contains(const char * str, int size, const char token)
{
	for (int i = 0; i < size; i++)
	{
		if (str[i] == token)
		{
			return true;
		}
	}
	return false;
}