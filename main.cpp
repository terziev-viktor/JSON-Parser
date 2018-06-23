#include "JSONParser.h"
using interpreters::JSONParser;

// This is a .NET solution
// I'm using the Composite OOP Design Pattern
// Source::https://www.oodesign.com/composite-pattern.html

int main()
{
	JSONParser json;
	json.load("file.json");
	json.get(0)->print();

	return 0;
}