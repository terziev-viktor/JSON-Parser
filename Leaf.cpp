#pragma once

#include "Leaf.h"
#include "Number.h"
using components::Leaf;
using components::Component;

#include <iostream>
#include <string>
using std::string;
using std::cout;

Leaf::Leaf()
{
	this->value = nullptr;
}

components::Leaf::Leaf(const char * name, Component * value)
{
	this->setName(name);
	this->value = value;
}

Leaf::~Leaf()
{
	if(value)
	delete this->value;
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

void components::Leaf::setName(const char * name)
{
	strcpy_s(this->name, sizeof(this->name), name);
}

void components::Leaf::setName(const string & name)
{
	this->setName(name.c_str());
}

void components::Leaf::setValue(Component * value)
{
	this->value = value;
}

