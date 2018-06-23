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
}

JSONParser::~JSONParser()
{
	delete this->list;
}

const Component * JSONParser::get(unsigned int index) const
{
	return this->list->getAt(index);
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

bool JSONParser::load(const char * path)
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
	Vector<Token> tokens = Tokenizer::tokenize(this->file);
	Vector<Token>::Iterator i = tokens.createIterator();
	this->list = ComponentFactory::getFactory().createFromTokens(i);
	return true;
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