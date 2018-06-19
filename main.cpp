#include "JSONParser.h"
#include "ComponentFactory.h"
#include "Composite.h"
#include "Number.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using namespace tools;
using namespace components;
using namespace factory;
using namespace interpreters;

// This is a .NET solution
// I'm using the Composite OOP Design Pattern
// Source::https://www.oodesign.com/composite-pattern.html

int main()
{
	Composite json;
	json.addLeaf(new Leaf("one", new Number(4.13)));
	json["one"]->print();

	return 0;
}