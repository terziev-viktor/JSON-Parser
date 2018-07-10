#pragma once
#include "Component.h"
#include "cstring.h"
using tools::cstring;

namespace components
{
	class Number : public Component
	{
	public:
		Number();
		Number(const cstring & other);
		Number(const double v);
		static const double EPS;

		const double get_value() const;
		void set_value(const cstring &);
		void set_value(const double v);
		Number & operator=(const double value);

		// Operators
		bool operator<(const Number & other) const;
		bool operator<=(const Number & other) const;
		bool operator>(const Number & other) const;
		bool operator>=(const Number & other) const;
		bool operator==(const Number & other) const;
		Number & operator+=(const Number & other);
		Number & operator-=(const Number & other);
		Number & operator*=(const Number & other);
		Number & operator/=(const Number & other);
		/*override Component*/
		Component * copy() const;
		const unsigned int size() const;
		void print(std::ostream & out, bool pretty, unsigned int tab_index) const;
		bool equals(const Component & other) const;
		cstring tell_type() const;
	private:
		double value;
	};
	Number operator+(const Number & a, const Number & b);
	std::ostream & operator<<(std::ostream &, const Number & n);

	namespace creators
	{
		class NumberCreator : public ComponentCreator
		{
		public:
			Component * createComponent(TokensSimulator & tokens, unsigned int & line_number) const;
		};
	}
}
