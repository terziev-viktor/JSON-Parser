#include "JSONParser.h"
#include "json_exceptions.hpp"
using namespace json_exceptions;
using interpreters::JSONParser;
// This is a .NET solution
// I'm using the Composite OOP Design Pattern
// Source::https://www.oodesign.com/composite-pattern.html

int main()
{
	Composite *a = new Composite();
	a->add("a", "bbb");
	Composite * b = new Composite();
	b->add("b", "bbbb");
	b->add("c", "bbbb");
	b->add("d", "bbbb");
	b->add("e", "bbbb");
	*a = b;
	a->print();
	b->print();
	delete a;
	delete b;
	return 0;
}