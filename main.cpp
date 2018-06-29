#include "JSONParser.h"
#include "json_exceptions.hpp"
using namespace json_exceptions;
using interpreters::JSONParser;
#include <iostream>
#include "Composite.h"
using components::Composite;
using std::cin;
using std::cout;
// This is a .NET solution
// I'm using the Composite OOP Design Pattern
// Source::https://www.oodesign.com/composite-pattern.html
// Abstract Factory OOP Design Pattern
// Source::https://learn.fmi.uni-sofia.bg/mod/folder/view.php?id=100016

const size_t COMMANDS_COUNT = 10;
const char COMMANDS[COMMANDS_COUNT][10] = { "exit", "help", "load", "parse", "select", "print", "save", "array_add", "json_add", "update" };

void show_help()
{
	cout << "commands:" << endl;
	cout << "-- exit : exit the demo" << endl;
	cout << "-- help : show help" << endl;
	cout << "-- load <string::path.json> : loads <path.json> file to the parser" << endl;
	cout << "-- parse : parses the loaded json file" << endl;
	cout << "-- select <int::n> : selects the n'th parsed value" << endl;
	cout << "-- print : prints the selected value" << endl;
	cout << "-- save <string::path> <bool::override file if it exists> <bool::pretty> : saves the selected value" << endl;
	cout << "-- array_add <int::n> <string::str1> ... <string::strn> : adding n parsed strings to currently selected array" << endl;
	cout << "-- json_add <int::n> <string::key1> <string::value1> ... <string::keyn> <string::valuen> : adding n parsed strings to currently selected json" << endl;
	cout << "-- update <int/string::index> <string::json_value> : updates currently selected element on index with parsed json_value" << endl;
}

void run()
{
	JSONParser parser;
	Indexable * current = nullptr;
	while (true)
	{
		try
		{
			char inp[20];
			cout << ">";
			cin >> inp;
			size_t command_index = -1;
			for (size_t i = 0; i < COMMANDS_COUNT; i++)
			{
				if (strcmp(COMMANDS[i], inp) == 0)
				{
					command_index = i;
				}
			}
			switch (command_index)
			{
			case 0: // exit
			{
				return;
				break;
			}
			case 1: // help
			{
				show_help();
				break;
			}
			case 2: // load
			{
				char path[20];
				cin >> path;
				parser.load(path);
				cout << path << " loaded ";
				break;
			}
			case 3: // parse
			{
					bool success = parser.parse();
				cout << (success ? "parse successful" : "error");
				break;
			}
			case 4: // select
			{
				int i;
				cin >> i;
				cin.get();
				current = &parser[i];
				char buffer[20];
				cin.getline(buffer, sizeof(buffer));
				String str(buffer);
				if (str.getLen() > 0)
				{
					Vector<String> s = str.split('.');
					for (size_t i = 0; i < s.count(); i++)
					{
						const char * c = s.getAt(i).getValue();
						current = &(*current)[c];
					}
				}
				cout << "selected";
				break;
			}
			case 5: // print
			{
				if (current)
				{
					current->print();
				}
				else
				{
					cout << "type select <int::n> to select a parsed value";
				}
				break;
			}
			case 6: // save
			{
				char path[20];
				bool over = true;
				bool pretty = true;
				cin >> path;
				cin >> over;
				cin >> pretty;
				parser.save(path, over, pretty);
				cout << "file saved" << endl;
				break;
			}
			case 7: // array_add
			{
				int n;
				cin >> n;
				for (size_t i = 0; i < n; i++)
				{
					char buffer[100];
					cin >> buffer;
					(*current).add(buffer);
				}
				cout << "added " << n << " element(s)";
				break;
			}
			case 8: // json_add
			{
				int n;
				cin >> n;
				for (size_t i = 0; i < n; i++)
				{
					char key[100];
					char value[100];
					cin >> key;
					cin >> value;
					(*current).add(key, value);
				}
				cout << "added " << n << " key value pairs";
				break;
			}
			case 9: // update
			{
				char index[20];
				cin >> index;
				char json[200];
				cin.ignore();
				cin.getline(json, 200);
				(*current).update(index, json);
			}
			default:
				cout << "Invalid command. type \"help\" to see the commands of the demo";
				break;
			}
			cout << endl;
		}
		catch (const std::exception& e)
		{
			cout << e.what() << endl;
		}
	}
}

int main()
{
	run();
	return 0;
}