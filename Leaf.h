#pragma once
#include "Component.h"
//using factory::ComponentCreator;

#include <string>
using std::string;
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
		void setName(const char * name);
		void setName(const string & name);
		void setValue(Component * value);

    private:
    	char name[100];
		Component * value;
    };
}
