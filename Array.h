#pragma once

#include "Indexable.h"
#include "tools\List.hpp"
using tools::List;

namespace components
{
	class Array : public Indexable
	{
	public:
		Array();
		Array(const Array & other);
		~Array();

		void add(Component * item);
		void add(const char * json);
		void add(double number);

		void remove(unsigned int index);

		const unsigned int size() const;
		const bool empty() const;
		const bool contains(const char * item, Component *& out) const;
		
		Array & operator=(const Array & other);
		Array & operator+=(Array & other);
		Array & operator-=(unsigned int index);
		bool operator==(const Array & other) const;

		/*override Indexable*/
		const Component & get(int index) const;
		Component & get(int index);
		const Component & get(const char * key)const;
		Component & get(const char * key);
		// updates:
		void update(const char * key, const char * json);
		void update(int index, const char * json);
		void update(int index, double number);
		void update(const char * key, double number);
		void update(const char * key, Component * new_value);
		void update(int index, Component * new_value);

		Indexable & operator[](int index);
		Indexable & operator[](const char * key);
		const Indexable & operator[](const char * key) const;
		const Indexable & operator[](int index) const;

		/*override component*/
		Component & operator=(const Component * other);
		Component & operator=(const Component & other);
		Component * copy() const;
		bool operator==(const Component * other) const;
		bool operator==(const Component & other) const;
		void print(unsigned short tab_index = 0, bool pretty = true) const;
		void print(std::ostream & out, unsigned short tab_index = 0, bool pretty = true) const;
	private:
		List<Component> values;
	};
	
	class ArrayCreator :public ComponentCreator
	{
	public:
		ArrayCreator();
		Component * createComponent(Vector<Token>::Iterator & i, unsigned int & line_number) const;
	};

	static ArrayCreator theArrayCreator;
}
