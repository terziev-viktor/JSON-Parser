#pragma once

#include "Leaf.h"
using components::Leaf;

#include <iostream>
using std::cout;

Leaf::Leaf()
{

}

Leaf::Leaf(const char *name, const char * value)
{
    strcpy_s(this->name, sizeof(this->name), name);
    strcpy_s(this->value, sizeof(this->value), value);
}

Leaf::~Leaf()
{

}

void Leaf::print() const
{
    cout << name << ':' << value;
}

