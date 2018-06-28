#include "JSONParser.h"
#include "json_exceptions.hpp"
using namespace json_exceptions;
using interpreters::JSONParser;
// This is a .NET solution
// I'm using the Composite OOP Design Pattern
// Source::https://www.oodesign.com/composite-pattern.html
// Abstract Factory OOP Design Pattern
// Source::https://learn.fmi.uni-sofia.bg/mod/folder/view.php?id=100016

int main()
{
	JSONParser parser;
	parser.load("file.json");
	
	try
	{
		parser.parse();
		for (size_t i = 0; i < parser.getParsedCount(); i++)
		{
			parser[i].print();
			cout << endl;
		}
		cout << endl;
	}
	catch (const json_exceptions::bad_json_exception & e)
	{
		cout << e.what() << " @ line " << e.get_line_number() << endl;
	}
	

	return 0;
}