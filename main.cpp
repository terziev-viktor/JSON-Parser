
#include "tools/List.hpp"
#include "Composite.h"
#include "Leaf.h"

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
    json.addChild(new Leaf("name1", "val"));
    json.addChild(new Leaf("name2", "val"));
    json.addChild(new Leaf("name3", "val"));
    json.addChild(new Composite());
    json.print();
	return 0;
}