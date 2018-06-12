#pragma once
#include "Component.h"
//using factory::ComponentCreator;

#include <cstring>

namespace components
{
	// This is a component with no children
	// It represents the key-value-pairs in json format
    class Leaf : public Component
    {
    public:
    	Leaf();
    	Leaf(const char * name, Component * value);
    	~Leaf();
		void print() const;
		void print(std::ostream & out) const;
		const Component * getValue() const;
		const char * getName() const;

    private:
    	char name[100];
		Component * value;
    };

	class LeafCreator : public ComponentCreator
	{
	public:
		LeafCreator();

		Component * createComponent(std::ifstream & in) const;
	};

	static LeafCreator theLeafCreator;
}
