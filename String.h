#pragma once
#include "Component.h"

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

		// override virtual function
		void print() const;

		// Operators
		bool String::operator==(const String & other) const;
		String & String::operator+=(const String & other);
	private:
		char * value;
	};
}