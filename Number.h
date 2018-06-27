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
		/*override*/bool operator==(const Component * other) const;
		/*override*/bool operator==(const Component & other) const;
		/*override*/Component & operator=(const Component * other);
		/*override*/Component & operator=(const Component & other);
		/*override*/Component * copy() const;
		Number & operator+=(const Number & other);
		Number & operator-=(const Number & other);
		Number & operator*=(const Number & other);
		Number & operator/=(const Number & other);
		/*override*/void print(unsigned short tab_index = 0, bool pretty = true) const;
		/*override*/void print(std::ostream & out, unsigned short tab_index = 0, bool pretty = true) const;
	private:
		double value;
		
	};
}
