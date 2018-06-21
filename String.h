#pragma once
#include "Component.h"

//using factory::ComponentCreator;
namespace components
{
	class String : public Component
	{
	public:
		String();
		String(size_t capacity);
		String(const String & other);
		// value should be a string ending with '\0'
		String(const char * value);
		~String();
		const char * getValue() const;
		const size_t getLen() const;
		String substring(size_t from, size_t to) const;
		const int firstIndexOf(const char c, size_t start_from = 0) const;
		const int firstIndexOf(const char * c, size_t start_from = 0) const;

		const char charAt(unsigned int at) const;
		void setValue(const char * value);
		void setValue(const char c);
		const bool startsWith(const char ch) const;

		// override virtual function
		void print() const;
		void print(std::ostream & out) const;

		// Operators
		String & operator=(const char * other);
		String & operator=(const char c);
		String & operator=(const String & other);
		bool operator==(const String & other) const;
		bool operator==(const char * other) const;
		String & operator+=(const String & other);
		String & operator+=(const char * other);
		String & operator+=(const char ch);
		const char operator[](int index) const;
		char & operator[](int index);
	private:
		char * value;
		size_t length;
		size_t capacity;
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

