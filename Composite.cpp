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
    cout << "{\n";

    for (size_t i = 0; i < this->children.count(); ++i)
    {
        cout << "\t";
        children.getAt(i)->print();
        cout << endl;
    }

    cout << "}\n";
}

const Component * Composite::getChild(int at) const
{
    return this->children.getAt(at);
}

void Composite::addChild(Component * child)
{
    this->children.add(child);
}
