#pragma once
#include "Component.h"
#include <cstring>

namespace components
{
	// This is a component with no children
	// It represents the key-value-pairs in json format
    class Leaf : public Component
    {
    public:
    	Leaf();
    	Leaf(const char * name, const char * value);
    	~Leaf();
    	void print() const;
    private:
    	char name[100];
    	char value[100];
    };
}
