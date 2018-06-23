#pragma once
#include "Leaf.h"
#include "tools/List.hpp"
#include "String.h"
#include "Number.h"
#include "ComponentFactory.h"
using factory::ComponentFactory;
using components::String;
using components::Number;
using namespace tools;
//using factory::ComponentCreator;

namespace components
{
	// This is a components with children other components (Leafs or Composites)
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
		Component * createComponent(Vector<Token>::Iterator & i) const;
	};

	static CompositeCreator theCompositeCreator;
}
