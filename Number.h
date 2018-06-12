#pragma once
#include "Component.h"
#include <fstream>
//using factory::ComponentCreator;

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
		bool operator<(const Number & other) const;
		bool operator>(const Number & other) const;
		bool operator==(const Number & other) const;
		Number & operator+=(const Number & other);
		Number & operator-=(const Number & other);
		Number & operator*=(const Number & other);
		Number & operator/=(const Number & other);
		void print() const;
		void print(std::ostream & out) const;
	private:
		double value;
		
	};

	class NumberCreator : public ComponentCreator
	{
	public:
		NumberCreator();
		Component * createComponent(std::ifstream & in) const;
	};

	static NumberCreator theNumberCreator;
}
