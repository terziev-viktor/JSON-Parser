#pragma once
#include "tools\List.hpp"
using tools::List;
#include "JSONParser.h"
using interpreters::JSONParser;

namespace components
{
	class Array : public Indexable
	{
	public:
		Array();
		Array(const Array & other);
		Array(const Indexable & other);
		~Array();

		void add(Component * item);
		
		const unsigned int size() const;
		const bool empty() const;
		
		Array & operator=(const Array & other);
		Array & operator+=(const Array & other);
		Array & operator-=(unsigned int index);
		bool operator==(const Array & other) const;

		/*override Modifiable*/
		void add(unsigned int items_count, ...);
		void add(const char * json);
		void add(const char * json1, const char * json2);
		void update(const char * key, const char * json);
		void update(int index, const char * json);
		void update(int index, double number);
		void update(const char * key, double number);
		void update(const char * key, Component * new_value);
		void update(int index, Component * new_value);
		void remove(const char * index);
		void remove(int index);
		void swap(const char * key1, const char * key2);
		void swap(unsigned int index1, unsigned int index2);

		/*override Indexable*/
		const Component & get(int index) const;
		Component & get(int index);
		const Component & get(const char * key)const;
		Component & get(const char * key);
		Indexable & operator=(const Indexable & other);
		Indexable & operator+=(const Indexable & other);
		Indexable & operator[](int index);
		Indexable & operator[](const char * key);
		const Indexable & operator[](const char * key) const;
		const Indexable & operator[](int index) const;
		const const bool contains(const char * item, Component * out) const;

		/*override component*/
		Component & operator=(const Component & other);
		Component & operator+=(const Component & other);
		Component * copy() const;
		bool operator==(const Component & other) const;
		bool operator!=(const Component & other) const;
		void print(unsigned short tab_index = 0, bool pretty = true) const;
		void print(std::ostream & out, unsigned short tab_index = 0, bool pretty = true) const;
	private:
		List<Component> values;
		void copyFrom(const Array & other);
	};
	
	class ArrayCreator :public ComponentCreator
	{
	public:
		ArrayCreator();
		Component * createComponent(Vector<Token>::Iterator & i, unsigned int & line_number) const;
	};
	Array operator+(const Array & left, const Array & right);
}
