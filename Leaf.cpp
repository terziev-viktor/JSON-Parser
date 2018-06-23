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

void components::Leaf::print(unsigned short tab_index) const
{
	print(cout, tab_index);
}

void components::Leaf::print(std::ostream & out, unsigned short tab_index) const
{
	out << "\"" << name << "\"" << ':';
	this->value->print(out, tab_index);
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

Component * components::Leaf::operator[](unsigned int index)
{
	return this->value;
}

const Component * components::Leaf::operator[](unsigned int index) const
{
	return this->value;
}

