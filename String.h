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
		String(size_t capacity);
		String(const String & other);
		String(const string & other);
		// value should be a string ending with '\0'
		String(const char * value);
		~String();
		const char * getValue() const;
		const size_t getLen() const;
		String substring(size_t from, size_t to) const;
		const int find_first(const char c, size_t start_from = 0) const;
		const int find_first_of(const char * c, size_t start_from = 0) const;

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
		/*override*/Component & operator=(Component * other);
		/*override*/bool operator==(const Component * other) const;
		/*override*/bool operator==(const Component & other) const;
		bool operator==(const String & other) const;
		bool operator==(const char * other) const;
		String & operator+=(const String & other);
		String & operator+=(const char * other);
		String & operator+=(const char ch);
		const components::Component * operator[](unsigned int index) const;
		components::Component * operator[](unsigned int index);
	private:
		char * value;
		size_t length;
		size_t capacity;
	};
	std::ostream & operator<<(std::ostream&, const String &);
}

