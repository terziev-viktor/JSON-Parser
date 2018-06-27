#pragma once
#include "Leaf.h"
#include "String.h"
#include "Number.h"
#include "Indexable.h"
#include "ComponentFactory.h"
using factory::ComponentFactory;
using components::String;
using components::Number;
//using factory::ComponentCreator;

namespace components
{
	// This is a components with children other components (Leafs or Composites)
    class Composite : public Indexable
    {
    public:
		Composite();
		Composite(const Composite & other);
    	~Composite();
	
		const bool hasKey(const char * key) const;
		

		/*override Indexable*/
		const Component & get(const char * name) const;
		Component & get(const char * name);
		const Component & get(int index) const;
		Component & get(int index);
		void update(const char * key, const char * json);
		void update(int index, const char * json);
		void update(int index, double number);
		void update(const char * key, double number);
		void update(const char * key, Component * new_value);
		void update(int index, Component * new_value);
		const Indexable & operator[](const char * key) const;
		Indexable & operator[](const char * key);
		const Indexable & operator[](int index) const;
		Indexable & operator[](int index);

		void add(const char * name, const char * value);
		void add(const Leaf & l);

		void remove(const char * key);
		void swap(const char * keyA, const char * keyB);
		bool operator==(const Composite & other) const;
		Composite & operator+=(const Composite & other);
		Composite & operator=(const Composite & other);

		/*override Component*/ 
		Component & operator=(const Component * other);
		Component & operator=(const Component & other);
		Component * copy() const;
		bool operator==(const Component * other) const;
		bool operator==(const Component & other) const;
		void print(unsigned short tab_index = 0, bool pretty = true) const;
		void print(std::ostream & out, unsigned short tab_index = 0, bool pretty = true) const;
    private:
    	Vector<Leaf> leafs;
		Leaf & findLeaf(const char * key);
		const Leaf & findLeaf(const char * key) const;
		void update(Leaf & l, const char * json);
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
