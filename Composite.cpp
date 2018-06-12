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

	for (size_t i = 0; i < this->children.count(); ++i)
	{
		out << '\t';
		children.getAt(i)->print(out);
		out << endl;
	}

	out << "}\n";
}

const Component * Composite::getChild(int at) const
{
    return this->children.getAt(at);
}

void Composite::addChild(Component * child)
{
    this->children.add(child);
}

components::CompositeCreator::CompositeCreator()
	:ComponentCreator('{', '}', "composite")
{
}

Component * components::CompositeCreator::createComponent(std::ifstream & in) const
{
	return new Composite();
}
