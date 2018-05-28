
#include "tools/List.hpp"
#include "Composite.h"
#include "Leaf.h"
#include "Array.h"
#include "String.h"
#include "Number.h"

#include <iostream>
#include <vector>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using namespace tools;
using namespace components;

// This is a .NET solution
// I'm using the Composite OOP Design Pattern
// Source::https://www.oodesign.com/composite-pattern.html

int main()
{
    Composite json;
    json.addChild(new Leaf("name1", new String("value1")));
    json.addChild(new Leaf("name2", new String("value2")));
	json.addChild(new Leaf("name3", new Number(222.222)));
	Array * arr = new Array();
	arr->add(new String("first"));
	arr->add(new String("Second"));
	arr->add(new Number(7.77));
	Composite * composite = new Composite();
	composite->addChild(new Leaf("arr", arr));
	json.addChild(new Leaf("anotherObject", composite));
	json.print();

	return 0;
}