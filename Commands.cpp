#include "Commands.h"
#include "Number.h"
using namespace components;
using namespace commands;

Command::Command()
{
}

commands::Command::Command(const char * trigger)
{
	this->setTrigger(trigger);
}


Command::~Command()
{
}

void commands::Command::setTrigger(const char * t)
{
	this->trigger = t;
}

void commands::Command::setTrigger(const String & t)
{
	this->trigger = t;
}

const String & commands::Command::getTrigger() const
{
	return this->trigger;
}

Vector<String> commands::Command::readArgs(char delim) const
{
	char inp[100];
	std::cin.getline(inp, 100, '\n');
	String args_str = inp;
	Vector<String> args = args_str.split(delim);
	return args;
}

String commands::Command::readArg() const
{
	char inp[100];
	std::cin.getline(inp, 100, '\n');
	String arg = inp;
	return arg;
}

void commands::Help::execute(Indexable *& current, JSONParser & parser)
{
	cout << "commands:" << endl;
	cout << "-- exit : exit the demo" << endl;
	cout << "-- help : show help" << endl;
	cout << "-- load <string::path.json> : loads <path.json> file to the parser and parses all object in it." << endl;
	cout << "-- select <string::path> : selects an object from the parser's parsed objects. The first parsed object is 0, then 1 and so on. Then you type keys like so: 0.key1.key2" << endl;
	cout << "-- print : prints the selected value" << endl;
	cout << "-- save <string::path> <bool::override file if it exists> <bool::pretty> : saves the selected value" << endl;
	cout << "-- array_add <string::str1> ... <string::strn> : adding n parsed strings to currently selected array" << endl;
	cout << "-- json_add <string::key1> <string::value1> ... <string::keyn> <string::valuen> : adding n parsed strings to currently selected json" << endl;
	cout << "-- update <int/string::index> <string::json_value> : updates currently selected element on index with parsed json_value" << endl;
	cout << "-- swap <string/int::key1> <string/int::key2> : swaps values of key1 and key2" << endl;
	cout << "-- remove <string/int::key> : removes the element on index key";
}

void commands::Load::execute(Indexable *& current, JSONParser & parser)
{
	Vector<String> args = this->readArgs(' ');

	parser.load(args[0].getValue());
	cout << args[0].getValue() << " loaded " << endl;
	bool success = parser.parse();
	cout << (success ? "parse successful" : "error");
}

void commands::Select::execute(Indexable *& current, JSONParser & parser)
{
	Vector<String> keys = this->readArgs('.');

	int index;
	if (!Number::tryParse(keys[0].getValue(), index))
	{
		cout << "Invalid index for parser's parsed value. Try numbers from greater or equal to 0";
	}
	current = &parser[index];
	try
	{
		for (size_t i = 1; i < keys.count(); i++)
		{
			const char * c = keys.getAt(i).getValue();
			current = &(*current)[c];
		}
		cout << "selected " << index << '.';
		for (size_t i = 1; i < keys.count(); i++)
		{
			cout << keys[i].getValue() << '.';
		}
	}
	catch (const std::bad_cast&)
	{
		cout << "Can't select non-indexable object";
	}

}

void commands::Print::execute(Indexable *& current, JSONParser & parser)
{
	if (current)
	{
		current->print();
	}
	else
	{
		cout << "type select <string::path> to select a object to print";
	}
}

void commands::Save::execute(Indexable *& current, JSONParser & parser)
{
	Vector<String> args = this->readArgs(' ');
	if (!current)
	{
		cout << "first, select an object to save";
		return;
	}
	bool overFile, pretty;
	overFile = (args[1] == '1') ? true : false;
	pretty = (args[2] == '1') ? true : false;
	parser.save(current, args[0].getValue(), overFile, pretty);
	cout << "file saved to " << args[0].getValue();
}

void commands::ArrayAdd::execute(Indexable *& current, JSONParser & parser)
{
	Vector<String> args = this->readArgs(' ');
	if (!current)
	{
		cout << "first, select an array object";
		return;
	}
	for (size_t i = 0; i < args.count(); i++)
	{
		(*current).add(args[i].getValue());
	}
	cout << "added " << args.count() << " element(s)";
}

void commands::JsonAdd::execute(Indexable *& current, JSONParser & parser)
{
	Vector<String> args = this->readArgs(' ');
	if (!current)
	{
		cout << "select an object first";
		return;
	}
	int n = args.count() / 2;
	for (size_t i = 0; i < args.count(); i += 2)
	{
		(*current).add(args[i].getValue(), args[i + 1].getValue());
	}
	cout << "added " << n << " key value pairs";
}

void commands::Update::execute(Indexable *& current, JSONParser & parser)
{
	char key[50];
	std::cin >> key;
	std::cin.ignore();
	String arg = this->readArg();

	if (!current)
	{
		cout << "select an object first";
		return;
	}
	(*current).update(key, arg.getValue());
	cout << "updated " << key << " to " << arg;
}

void commands::Swap::execute(Indexable *& current, JSONParser & parser)
{
	Vector<String> args = this->readArgs(' ');

	current->swap(args[0].getValue(), args[1].getValue());
	cout << "swapped " << args[0].getValue() << " with " << args[1].getValue();
}

void commands::Remove::execute(Indexable *& current, JSONParser & parser)
{
	Vector<String> args = this->readArgs(' ');

	for (size_t i = 0; i < args.count(); i++)
	{
		current->remove(args[i].getValue());
		cout << "removed " << args[i].getValue() << " ";
	}
}
