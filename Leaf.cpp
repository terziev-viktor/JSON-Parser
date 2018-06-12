#pragma once

#include "Leaf.h"
#include "Number.h"
using components::Leaf;
using components::Component;

#include <iostream>
using std::cout;

Leaf::Leaf()
{

}

components::Leaf::Leaf(const char * name, Component * value)
{
	strcpy_s(this->name, sizeof(this->name), name);
	this->value = value;
}

Leaf::~Leaf()
{

}

void Leaf::print() const
{
	print(cout);
}

void components::Leaf::print(std::ostream & out) const
{
	out << name << ':';
	this->value->print(out);
}

const Component * components::Leaf::getValue() const
{
	return this->value;
}

const char * components::Leaf::getName() const
{
	return this->name;
}

components::LeafCreator::LeafCreator()
	:ComponentCreator("leaf")
{
}

Component * components::LeafCreator::createComponent(std::ifstream & in) const
{
	return new Leaf("leaf", new Number(2.22));
}
