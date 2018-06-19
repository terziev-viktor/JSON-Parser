#pragma once
#include "Component.h"
#include <iostream>

//using factory::ComponentCreator;
namespace components
{
	class String : public Component
	{
	public:
		String();
		// value should be a string ending with '\0'
		String(const char * value);
		~String();
		const char * getValue() const;
		const size_t getLen() const;

		const char charAt(int at) const;
		void setValue(const char * value);
		bool startsWith(const char ch);

		// override virtual function
		void print() const;
		void print(std::ostream & out) const;

		// Operators
		bool operator==(const String & other) const;
		String & operator+=(const String & other);
		String & operator+=(const char * other);
		const char operator[](int index) const;
		char& operator[](int index);
	private:
		char * value;
	};

	class StringCreator : public ComponentCreator
	{
	public:
		StringCreator();
		Component * createComponent(std::ifstream & in) const;
	};

	static StringCreator theStringCreator;

	std::ostream & operator<<(std::ostream&, const String &);
}

