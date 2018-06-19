#pragma once
#include "Leaf.h"
#include "tools/List.hpp"
using namespace tools;
//using factory::ComponentCreator;

namespace components
{
	// This is a components with children other components (Leafs ot Composites)
    class Composite : public Component
    {
    public:
		Composite();
    	~Composite();
		void print() const;
		void print(std::ostream & out) const;
		// gets the n'th leaf
		const Leaf * getLeaf(int n) const;
		Leaf * getLeaf(int n);
		// Gets the leaf by name. throws const char * errmsg of the name does not exist
		const Leaf * getLeaf(const char * name) const;
		Leaf * getLeaf(const char * name);
    	void addLeaf(Leaf * child);

		const Leaf * operator[](int n) const;
		Leaf * operator[](int n);
		const Leaf * operator[](const char * name) const;
		Leaf * operator[](const char * name);

    private:
    	List<Leaf> leafs;
    };

	class CompositeCreator : public ComponentCreator
	{
	public:
		CompositeCreator();
		Component * createComponent(std::ifstream & in) const;
	};

	static CompositeCreator theCompositeCreator;
}
