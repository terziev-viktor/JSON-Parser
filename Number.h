#pragma once
#include "Component.h"
#include <string>
using std::string;
#include <fstream>
//using factory::ComponentCreator;

namespace components
{
	class Number : public Component
	{
	public:
		Number();
		Number(const Number & other);
		Number(const string & str);
		Number(const double v);
		~Number();
		static const double EPS;
		static bool tryParse(const char * str, int & out);

		void setValue(double v);
		const double getValue() const;
		Number & operator=(const Number & other);

		// Operators
		bool operator<(const Number & other) const;
		bool operator>(const Number & other) const;
		bool operator==(const Number & other) const;
		Number & operator+=(const Number & other);
		Number & operator-=(const Number & other);
		Number & operator*=(const Number & other);
		Number & operator/=(const Number & other);
		/*override Component*/
		bool operator==(const Component * other) const;
		bool operator==(const Component & other) const;
		bool operator!=(const Component * other) const;
		bool operator!=(const Component & other) const;
		Component & operator=(const Component * other);
		Component & operator=(const Component & other);
		Component & operator+=(const Component & other);
		Component * copy() const;
		void print(unsigned short tab_index = 0, bool pretty = true) const;
		void print(std::ostream & out, unsigned short tab_index = 0, bool pretty = true) const;
	private:
		double value;
		
	};
}
