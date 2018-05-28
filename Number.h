#pragma once
#include "Component.h"

namespace components
{
	class Number : public Component
	{
	public:
		Number();
		Number(const double v);
		~Number();
		static const double EPS;

		void setValue(double v);
		const double getValue() const;
		Number & operator=(const Number & other);

		// Operators
		bool Number::operator<(const Number & other) const;
		bool Number::operator>(const Number & other) const;
		bool Number::operator==(const Number & other) const;
		Number & operator+=(const Number & other);
		Number & operator-=(const Number & other);
		Number & operator*=(const Number & other);
		Number & operator/=(const Number & other);
		void print() const;
	private:
		double value;
		
	};
}
