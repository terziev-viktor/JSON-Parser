#pragma once
#include "Leaf.h"
#include "String.h"
#include "Number.h"
#include "ComponentFactory.h"
using factory::ComponentFactory;
using components::String;
using components::Number;
//using factory::ComponentCreator;

namespace components
{
	// This is a components with children other components (Leafs or Composites)
    class Composite : public Component
    {
    public:
		Composite();
		Composite(const Composite & other);
    	~Composite();
	
		const bool hasKey(const char * key) const;
		const Component * get(const char * name) const;
		Component * get(const char * name);
		const Component * operator[](const char * name) const;
		Component * operator[](const char * name);
		void add(const char * name, const char * value);
		void add(const Leaf & l);

		void update(const char * key, const char * json);

		// !! deletes !! the old value and sets a new one
		void update(const char * key, double number);

		void remove(const char * key);
		void swap(const char * keyA, const char * keyB);
		bool operator==(const Composite & other) const;
		Composite & operator+=(const Composite & other);
		Composite & operator=(const Composite & other);

		/*override*/Component & operator=(Component * other);
		/*override*/bool operator==(const Component * other) const;
		/*override*/bool operator==(const Component & other) const;
		/*override*/void print(unsigned short tab_index = 0, bool pretty = true) const;
		/*override*/void print(std::ostream & out, unsigned short tab_index = 0, bool pretty = true) const;
    private:
    	Vector<Leaf> leafs;
		Leaf & findLeaf(const char * key);
		bool leafExists(const char * key) const;
    };

	class CompositeCreator : public ComponentCreator
	{
	public:
		CompositeCreator();
		Component * createComponent(Vector<Token>::Iterator & i, unsigned int & line_number) const;
	};

	static CompositeCreator theCompositeCreator;
}
