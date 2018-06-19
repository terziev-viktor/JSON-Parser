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
	:ComponentCreator("composite")
{
}

Component * components::CompositeCreator::createComponent(std::ifstream & in) const
{
	return new Composite();
}
