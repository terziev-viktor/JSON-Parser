#pragma once
#include "tools\PointerContainer.hpp"
#include "String.h"
#include "JSON.h"
using tools::PointerContainer;

namespace components
{
	// This is a components with children other components (Leafs or Composites)
    class Composite : public JSON
    {
    public:
		~Composite();
		const Vector<String> get_keys() const;
		const PointerContainer<Component> & get_values() const;
		
		void add(const String & key, const Component & value);
		unsigned int count() const;
		int index_of(const Component & item) const;
		bool is_empty() const;
		void clear();

		/*override JSON*/
		JSON & get(const String & index);
		const JSON & get(const String & index) const;
		void swap(const String &key1, const String &key2);
		void add(unsigned int key_value_pairs_count, ...);
		void remove(const String & key);
		void update(const String & key, const Component & new_value);

		/*operators*/
		bool operator==(const Composite & other) const;
		Composite & operator+=(const Composite & other);
		Composite & operator=(const Composite & other);
		Component & operator[](const String & key);
		const Component & operator[](const String & key) const;

		/*override Component*/ 
		Component * copy() const;
		void print(std::ostream & out, bool pretty, unsigned int tab_index) const;
		bool equals(const Component & other) const;
		cstring tell_type() const;
    private:
    	Vector<String> keys;
		PointerContainer<Component> values;
    };
	namespace creators
	{
		class CompositeCreator : public ComponentCreator
		{
		public:
			Component * createComponent(TokensSimulator & tokens, unsigned int & line_number) const;
			static Composite * create_json(TokensSimulator & tokens, unsigned int & line_number);
		};
	}
}
