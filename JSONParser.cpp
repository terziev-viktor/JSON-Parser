#include "JSONParser.h"
#include <fstream>
#include "Tokenizer.h"
#include "ComponentFactory.h"
using factory::ComponentFactory;

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

const Component * JSONParser::get(unsigned int index) const
{
	return this->list->getAt(index);
}

Composite * interpreters::JSONParser::getAsJsonObject(unsigned int index)
{
	if (index >= 0 && index < this->list->count())
	{
		Component * obj = this->list->getAt(index);
		return dynamic_cast<Composite*>(obj);
	}
	return nullptr;
}

const Composite * interpreters::JSONParser::getAsJsonObject(unsigned int index) const
{
	if (index >= 0 && index < this->list->count())
	{
		Component * obj = this->list->getAt(index);
		return dynamic_cast<Composite*>(obj);
	}
	return nullptr;
}

Array * interpreters::JSONParser::getAsJsonArray(unsigned int index)
{
	if (index >= 0 && index < this->list->count())
	{
		Component * obj = this->list->getAt(index);
		return dynamic_cast<Array*>(obj);
	}
	return nullptr;
}

const Array * interpreters::JSONParser::getAsJsonArray(unsigned int index) const
{
	if (index >= 0 && index < this->list->count())
	{
		Component * obj = this->list->getAt(index);
		return dynamic_cast<Array*>(obj);
	}
	return nullptr;
}

Component * interpreters::JSONParser::get(unsigned int index)
{
	return this->list->getAt(index);
}

const unsigned int interpreters::JSONParser::getParsedCount() const
{
	return this->list->count();
}

const Component & interpreters::JSONParser::operator[](unsigned int index) const
{
	return *this->get(index);
}

Component & interpreters::JSONParser::operator[](unsigned int index)
{
	return *this->get(index);
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

bool interpreters::JSONParser::fileExists(const char * path)
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

bool interpreters::JSONParser::save(const char * path, bool overrideFile, bool pretty)
{
	size_t len = strlen(path);
	if (path[len - 1] != 'n' || path[len - 2] != 'o' || path[len - 3] != 's' || path[len - 4] != 'j' || path[len - 5] != '.')
	{
		throw std::invalid_argument("path must be .json file");
		return false;
	}
	if (!overrideFile && this->fileExists(path))
	{
		throw std::exception("File already exists. Set <overrideFile> parameter to true if you wish to override it");
		return false;
	}
	std::ofstream jsonFile;
	jsonFile.open(path);
	
	if (!jsonFile)
	{
		throw std::exception("Could not open file");
		return false;
	}
	for (size_t i = 0; i < this->list->count(); i++)
	{
		this->list->getAt(i)->print(jsonFile, 0, pretty);
	}
	jsonFile.close();
	return true;
}

Array * interpreters::JSONParser::findAll(const char * key)
{
	Array * arr = new Array();
	for (size_t i = 0; i < this->list->count(); i++)
	{
		Composite * c = this->getAsJsonObject(i);
		if (c && c->hasKey(key))
		{
			arr->add(c->get(key));
		}
		else
		{
			Array * casted = this->getAsJsonArray(i);
			Component * out;
			bool contains = casted->contains(key, out);
			if (casted && contains)
			{
				arr->add(out);
			}
		}
	}
	return arr;
}

bool contains(const char * str, int size, const char tocken)
{
	for (int i = 0; i < size; i++)
	{
		if (str[i] == tocken)
		{
			return true;
		}
	}
	return false;
}