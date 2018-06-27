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

components::Leaf::Leaf(const Leaf & other)
{
	this->setName(other.getName());
	this->value = other.value;
}

components::Leaf::Leaf(const char * name, Component * value)
{
	this->setName(name);
	this->value = value;
}

Leaf::~Leaf()
{
	if (value)
	{
		delete this->value;
	}
	
}

void components::Leaf::print(unsigned short tab_index, bool pretty) const
{
	print(cout, tab_index, pretty);
}

void components::Leaf::print(std::ostream & out, unsigned short tab_index, bool pretty) const
{
	out << "\"" << name << "\"" << ':';
	this->value->print(out, tab_index, pretty);
}

const Component * components::Leaf::getValue() const
{
	return this->value;
}

Component * components::Leaf::getValue()
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
	if (this->value)
	{
		delete this->value;
	}
	this->value = value;
}

Leaf & components::Leaf::operator=(const Leaf & other)
{
	this->setName(other.name);
	this->setValue(other.value->copy());
	return *this;
}

bool components::Leaf::operator==(const Leaf & other) const
{
	return *this->value == *other.value;
}

bool components::Leaf::operator==(const Component * other) const
{
	const Leaf * casted = dynamic_cast<const Leaf*>(other);
	if (casted)
	{
		return *this == *casted;
	}
	return false;
}

Component * components::Leaf::operator[](unsigned int index)
{
	return this->value;
}

const Component * components::Leaf::operator[](unsigned int index) const
{
	return this->value;
}

