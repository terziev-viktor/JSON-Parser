#include "Commands.h"
#include "Number.h"
using namespace components;
using namespace commands;
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;

commands::Command::Command(const cstring & trigger)
{
	this->set_trigger(trigger);
}

void commands::Command::set_trigger(const cstring & t)
{
	this->trigger = t;
}

const cstring & commands::Command::get_trigger() const
{
	return this->trigger;
}

Vector<cstring> commands::Command::read_args(const char * delim) const
{
	cstring str_args = this->read_arg();
	Vector<cstring> args = str_args.split(delim);
	return args;
}

cstring commands::Command::read_arg() const
{
	const short buffer_size = 100;
	char buffer[buffer_size];
	cstring args_str;
	std::cin.getline(buffer, buffer_size, '\n');
	args_str += buffer;
	return args_str;
}

void commands::Help::execute(JSON * &  parsed_json, JSON * &  current)
{
	cout << "commands:" << endl;
	cout << "--> exit : exit the demo" << endl;
	cout << "--> help : show help" << endl;
	cout << "--> load <string::path.json> : loads <path.json> file to the parser and parses all object in it." << endl;
	cout << "--> select <string::path> : selects an object from the parser's parsed objects. The first parsed object is 0, then 1 and so on. Then you type keys like so: 0.key1.key2" << endl;
	cout << "--> find (--save/--print/--clear) key_1...key_n : finds all elements by keys. Returns an array of copies of all found elements.\n\t--print prints the array,\n\t--save saves the array,\n\t--clear clears the content of the array " << endl;
	cout << "--> print : prints the selected value" << endl;
	cout << "--> save <string::path> <--override-file/--no> <--pretty/--min> : saves the selected value" << endl;
	cout << "--> add <string::str_1> ... <string::str_n> : adding n parsed strings to currently selected item (array or composite)" << endl;
	cout << "\tif the object is an array, every string is parsed and added" << endl;
	cout << "\tif the object is a composite, every odd string is parsed as a key and every even - as a value" << endl;
	cout << "--> update <int/string::index> <string::json_value> : updates currently selected element on index with parsed json_value" << endl;
	cout << "--> swap <string/int::key_1> <string/int::key_2> : swaps values of key1 and key2" << endl;
	cout << "--> remove <string/int::key> : removes the element on index key";
}

void commands::Load::execute(JSON * & parsed_json, JSON * &  current)
{
	cstring arg = this->read_arg();
	parsed_json = &JSONParser::parse_file(arg);
	if (!parsed_json)
	{
		throw bad_json_exception("Expected json object begin tokne '{' at the beginning of the file", 1);
	}
}

void commands::Select::execute(JSON * &  parsed_json, JSON * &  current)
{
	Vector<cstring> args = this->read_args(".");
	unsigned int i = 0;
	if (args[0] != "")
	{
		current = parsed_json;
	}
	else
	{
		i = 1;
	}
	String key;
	for (i; i < args.count(); i++)
	{
		key = args[i].get_as_char_array();
		current = &current->get(key);
	}
	cout << "selected ";
	for (size_t i = 0; i < args.count() - 1; i++)
	{
		cout << args[i] << '.';
	}
	cout << args[args.count() - 1];
}

void commands::Print::execute(JSON * &  parsed_json, JSON * &  current)
{
	if (current)
	{
		current->print(cout, true, 0);
	}
	else
	{
		cout << "Select an object first.";
	}
}

void commands::Save::execute(JSON * &  parsed_json, JSON * &  current)
{
	Vector<cstring> args = this->read_args(" ");
	std::ofstream out;
	if (args[1] == "--override-file")
	{
		out.open(args[0].get_as_char_array());
	}
	else
	{
		out.open(args[0].get_as_char_array(), std::ios::app);
	}
	try
	{
		current->print(out, args[2] == "--pretty", 0);
	}
	catch (const std::exception&)
	{
		out.close();
		throw;
	}
	out.close();
}

void commands::Update::execute(JSON * &  parsed_json, JSON * &  current)
{
	Vector<cstring> args = this->read_args(" ");

	String key(args[0].get_as_char_array());
	Component * value = JSONParser::parse(args[1]);
	if (!value)
	{
		cout << "Unknown format of value " << args[1];
		return;
	}
	try
	{
		current->update(key, *value);
	}
	catch (const std::exception&)
	{
		delete value;
		throw;
	}
	delete value;

}

void commands::Swap::execute(JSON * &  parsed_json, JSON * &  current)
{
	Vector<cstring> args = this->read_args(" ");
	String key1(args[0].get_as_char_array());
	String key2(args[1].get_as_char_array());
	current->swap(key1, key2);
	cout << "swapped " << key1 << " with " << key2;
}

void commands::Remove::execute(JSON * &  parsed_json, JSON * &  current)
{
	cstring arg = this->read_arg();
	String key(arg.get_as_char_array());
	current->remove(key);
	cout << "removed " << key;
}

void commands::Equal::execute(JSON * &  parsed_json, JSON * &  current)
{
	Vector<cstring> args = this->read_args(" ");
	String key1(args[0].get_as_char_array());
	String key2(args[1].get_as_char_array());
	Component & item1 = current->get(key1);
	Component & item2 = current->get(key2);
	bool compared = item1.equals(item2);
	cout << key1 << " is " << (compared ? "equal" : "not equal") << " to " << key2;
}

void commands::Find::execute(JSON * &  parsed_json, JSON * &  current)
{
	throw json_exception("Find command not implemented");
}

void commands::Find::search(Vector<cstring>& keys_to_search)
{
	throw json_exception("Not implemented");
}

void commands::Add::execute(JSON *& parsed_json, JSON *& current)
{
	Vector<cstring> args = this->read_args(" ");

	if (current->tell_type() == "Array")
	{
		Array * casted = dynamic_cast<Array *>(current);
		Component * parsed = nullptr;
		for (int i = 0; i < args.count(); i++)
		{
			parsed = JSONParser::parse(args[i]);
			if (!parsed)
			{
				throw json_exception("Unknown json format");
			}
			casted->add(*parsed);
			delete parsed;
			parsed = nullptr;
		}
		cout << "Added " << args.count() << " items";
	}
	else if (current->tell_type() == "Composite")
	{
		Composite * casted = dynamic_cast<Composite *>(current);
		Component * parsed = nullptr;
		for (int i = 0; i < args.count(); i += 2)
		{
			unsigned int line = 1;
			String * key = creators::StringCreator::create_string(TokensSimulator(args[i]), line);
			if (!key)
			{
				throw json_exception("Key must be a String");
			}
			parsed = JSONParser::parse(args[i + 1]);
			if (!parsed)
			{
				throw json_exception("Unknown json format");
			}
			try
			{
				casted->add(*key, *parsed);
			}
			catch (const std::exception&)
			{
				delete key;
				delete parsed;
				throw;
			}
			delete key;
			delete parsed;
			parsed = nullptr;
		}
		cout << "Added " << args.count() / 2 << " key-value pairs";
	}
	else
	{
		throw json_exception("Selected element can't add items");
	}
}
