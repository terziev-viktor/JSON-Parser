#pragma once

#include "Leaf.h"
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
    cout << name << ':';
	this->value->print();
}

const Component * components::Leaf::getValue() const
{
	return this->value;
}

const char * components::Leaf::getName() const
{
	return this->name;
}

