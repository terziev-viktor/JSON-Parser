#include "JSONParser.h"
#include "Composite.h"
#include <fstream>
using components::Composite;

using interpreters::JSONParser;

// This is a .NET solution
// I'm using the Composite OOP Design Pattern
// Source::https://www.oodesign.com/composite-pattern.html

int main()
{
	JSONParser parser;
	parser.parse("file.json");
	Component * json = parser[0];
	std::ofstream out;
	out.open("result.json");
	json->print(out);
	return 0;
}