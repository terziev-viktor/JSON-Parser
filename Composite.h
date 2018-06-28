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
		
		/*override Modifiable*/
		void add(unsigned int key_value_pairs_count, ...);
		void update(const char * key, const char * json);
		void update(int index, const char * json);
		void update(int index, double number);
		void update(const char * key, double number);
		void update(const char * key, Component * new_value);
		void update(int index, Component * new_value);
		void remove(const char * key);
		void remove(int index);

		/*override Indexable*/
		const Component & get(const char * name) const;
		Component & get(const char * name);
		const Component & get(int index) const;
		Component & get(int index);
		const Indexable & operator[](const char * key) const;
		Indexable & operator[](const char * key);
		const Indexable & operator[](int index) const;
		Indexable & operator[](int index);
		Indexable & operator=(const Indexable * other);
		Indexable & operator=(const Indexable & other);

		void add(const char * name, const char * value);
		void add(const Leaf & l);

		void swap(const char * keyA, const char * keyB);
		bool operator==(const Composite & other) const;
		Composite & operator+=(const Composite & other);
		Composite & operator=(const Composite & other);

		/*override Component*/ 
		Component & operator=(const Component * other);
		Component & operator=(const Component & other);
		Component & operator+=(const Component & other);
		Component * copy() const;
		bool operator==(const Component * other) const;
		bool operator==(const Component & other) const;
		bool operator!=(const Component * other) const;
		bool operator!=(const Component & other) const;
		void print(unsigned short tab_index = 0, bool pretty = true) const;
		void print(std::ostream & out, unsigned short tab_index = 0, bool pretty = true) const;
    private:
    	Vector<Leaf> leafs;
		Leaf & findLeaf(const char * key);
		const Leaf & findLeaf(const char * key) const;
		Leaf & findLeaf(const char * key, unsigned int & out);
		const Leaf & findLeaf(const char * key, unsigned int & out) const;
		void update(Leaf & l, const char * json);
		bool leafExists(const char * key) const;
    };

	class CompositeCreator : public ComponentCreator
	{
	public:
		CompositeCreator();
		Component * createComponent(Vector<Token>::Iterator & i, unsigned int & line_number) const;
	};
}
