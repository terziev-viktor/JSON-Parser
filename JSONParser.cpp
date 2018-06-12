#include "JSONParser.h"
using namespace interpreters;

JSONParser::JSONParser(const char * path)
{
	this->list = new List<Component>();
	this->load(path);
}

JSONParser::JSONParser(DynamicArray<Component>* list, const char * path)
{
	this->list = list;
	this->load(path);
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
		list->getAt(i)->print();
	}
}

void JSONParser::load(const char * path)
{
	cout << "loading" << endl;
}
