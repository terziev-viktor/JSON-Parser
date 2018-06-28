#pragma once
#include "Component.h"
#include <string>
using std::string;
//using factory::ComponentCreator;
namespace components
{
	class String : public Component
	{
	public:
		String();
		String(unsigned int capacity);
		String(const String & other);
		String(const string & other);
		// value should be a string ending with '\0'
		String(const char * value);
		~String();
		const char * getValue() const;
		const unsigned int getLen() const;
		String substring(unsigned int from, unsigned int to) const;
		const int find_first(const char c, unsigned int start_from = 0) const;
		const int find_first_of(const char * c, unsigned int start_from = 0) const;

		const char charAt(unsigned int at) const;
		void setValue(const char * value);
		void setValue(const char c);
		const bool startsWith(const char ch) const;

		/*override*/void print(unsigned short tab_index = 0, bool pretty = true) const;
		/*override*/void print(std::ostream & out, unsigned short tab_index = 0, bool pretty = true) const;

		// Operators
		String & operator=(const char * other);
		String & operator=(const char c);
		String & operator=(const String & other);
		String & operator=(const string & other);
		String & operator+=(const String & other);
		String & operator+=(const char * other);
		String & operator+=(const char ch);
		/*override Component*/
		Component & operator=(const Component * other);
		Component & operator=(const Component & other);
		Component & operator+=(const Component & other);
		Component * copy() const;
		bool operator==(const Component * other) const;
		bool operator==(const Component & other) const;
		bool operator!=(const Component * other) const;
		bool operator!=(const Component & other) const;
		bool operator==(const String & other) const;
		bool operator==(const char * other) const;
		
		const char operator[](unsigned int index) const;
		char operator[](unsigned int index);
	private:
		char * value;
		unsigned int length;
		unsigned int capacity;
	};
	std::ostream & operator<<(std::ostream&, const String &);
}

