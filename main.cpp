#include "JSONParser.h"
#include "json_exceptions.hpp"
using namespace json_exceptions;
using interpreters::JSONParser;
// This is a .NET solution
// I'm using the Composite OOP Design Pattern
// Source::https://www.oodesign.com/composite-pattern.html

int main()
{
	JSONParser parser;
	parser.load("file.json");
	
	try
	{
		parser.parse();

		parser[2].print();
		parser[2]["array"].update(0, "[1.2,3,4,5]");
		cout << endl;
		parser[2].print();

	}
	catch (const bad_json_exception& e)
	{
		cout << e.what() << " @ line " << e.get_line_number() << endl;
	}
	

	return 0;
}