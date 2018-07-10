#pragma once
#include "Component.h"
#include "Vector.hpp"
using tools::Vector;
using tools::cstring;
//using factory::ComponentCreator;
namespace components
{
	class String : public Component
	{
	public:
		String();
		String(unsigned int capacity);
		// value should be a string ending with '\0'
		String(const char * value);
		String(const String & other);
		~String();
		const char * get_value() const;
		unsigned int get_length() const;
		unsigned int get_capacity() const;
		String substring(unsigned int from, unsigned int to) const;
		const int find_first(const char c, unsigned int start_from = 0) const;
		const int find_first_of(const char * c, unsigned int start_from = 0) const;
		Vector<String> split(char delim) const;
		bool to_int(int & out) const;
		bool starts_with(const char ch) const;

		/*override Component*/
		void print(std::ostream & out, bool pretty, unsigned int tab_index) const;
		bool equals(const Component & other) const;

		// Operators
		String & operator+=(const String & other);
		String & operator+=(const char ch);
		bool operator==(const String & other) const;
		String & operator=(const String & other);
		/*override Component*/
		Component * copy() const;
		const unsigned int size() const;
		char operator[](unsigned int index) const;
		char & operator[](unsigned int index);
		cstring tell_type() const;
	private:
		char * value = nullptr;
		unsigned int length;
		unsigned int capacity;
	};
	String operator+(const String & a, const String & b);
	std::ostream & operator<<(std::ostream&, const String &);

	namespace creators
	{
		class StringCreator : public ComponentCreator
		{
		public:
			Component * createComponent(TokensSimulator & tokens, unsigned int & line_number) const;

			static String * create_string(TokensSimulator & tokens, unsigned int &);
		};
	}
}

