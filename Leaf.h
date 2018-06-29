#pragma once
#include "Component.h".
#include "Vector.hpp"
using tools::Vector;
//using factory::ComponentCreator;

#include <string>
using std::string;
namespace components
{
	// Represents the key-value-pairs in json format
    class Leaf
    {
    public:
		void print(unsigned short tab_index = 0, bool pretty = true) const;
		void print(std::ostream & out, unsigned short tab_index = 0, bool pretty = true) const;
		const Component * getValue() const;
		Component * getValue();
		const char * getName() const;
		void setName(const char * name);
		void setName(const string & name);
		void setValue(Component * value);
		Leaf & operator=(const Leaf & other);
		bool operator==(const Leaf & other) const;
		bool operator==(const char * str) const;
		bool operator==(const Component * other) const;
		Component * operator[](unsigned int index);
		const Component * operator[](unsigned int index) const;

		// friends
		friend class Composite;
		friend class CompositeCreator;
		friend class Vector<Leaf>;
    private:
    	char name[100];
		Component * value;

		Leaf();
		Leaf(const Leaf & other);
		Leaf(const char * name, Component * value);
		~Leaf();
    };
}
