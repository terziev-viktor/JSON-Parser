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
		String(unsigned int number_of_characters_to_store);
		String(const char * str);
		String(const cstring & str);
		const char * get_value() const;
		unsigned int get_length() const;
		unsigned int get_capacity() const;

		bool to_int(int & out) const;

		/*override Component*/
		void print(std::ostream & out, bool pretty, unsigned int tab_index) const;
		bool equals(const Component & other) const;
		Component * copy() const;
		// Operators
		String & operator+=(const String & other);
		String & operator+=(const char ch);
		bool operator==(const String & other) const;
		String & operator=(const String & other);
		
		char operator[](unsigned int index) const;
		char & operator[](unsigned int index);
		
	private:
		cstring value;
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

