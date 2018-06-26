#pragma once

#include "Component.h"
#include "tools\List.hpp"
using tools::List;

namespace components
{
	class Array : public Component
	{
	public:
		Array();
		Array(const Array & other);
		~Array();

		// Getters
		const Component & get(int at) const;
		Component & get(int at);
		Component & operator[](unsigned int index);
		const Component & operator[](unsigned int index) const;

		void add(Component * item);
		void add(const char * json);
		void add(double number);

		// Parses the string to json object
		// Deletes old value and sets new value at given index
		void update(unsigned int index, const char * json);

		void remove(unsigned int index);

		const unsigned int size() const;
		const bool empty() const;
		const bool contains(const char * item, Component *& out) const;
		
		Array & operator=(const Array & other);
		/*overrride*/Component & operator=(Component * other);
		Array & operator+=(Array & other);
		Array & operator-=(unsigned int index);
		bool operator==(const Array & other) const;

		/*override*/bool operator==(const Component * other) const;
		/*override*/bool operator==(const Component & other) const;
		/*override*/void print(unsigned short tab_index = 0, bool pretty = true) const;
		/*override*/void print(std::ostream & out, unsigned short tab_index = 0, bool pretty = true) const;
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
