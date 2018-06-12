#include "tools/List.hpp"
#include "Composite.h"
#include "Leaf.h"
#include "Array.h"
#include "String.h"
#include "Number.h"

#include "ComponentFactory.h"

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

// This is a .NET solution
// I'm using the Composite OOP Design Pattern
// Source::https://www.oodesign.com/composite-pattern.html

int main()
{
    Composite json;
	std::ifstream in;
    json.addChild(ComponentFactory::getFactory().create("number", in));
    json.addChild(ComponentFactory::getFactory().create("string", in));
	json.addChild(ComponentFactory::getFactory().create("leaf", in));
	json.addChild(ComponentFactory::getFactory().create("composite", in));
	json.addChild(ComponentFactory::getFactory().create("array", in));
	json.print(cout);

	
	
	return 0;
}