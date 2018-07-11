#include "Commands.h"
using namespace commands;
#include "JSONParser.h"
using std::cout;
using std::cin;
using std::endl;
using interpreters::JSONParser;
// This is a .NET solution
// I'm using the Composite OOP Design Pattern
// Source::https://www.oodesign.com/composite-pattern.html
// Abstract Factory OOP Design Pattern
// Source::https://learn.fmi.uni-sofia.bg/mod/folder/view.php?id=100016

void run_demo()
{
	JSONParser parser;
	JSON * current = nullptr;
	JSON * parsed = nullptr;
	PointerContainer<Command> executable_commands;
	executable_commands.add(new Help());
	executable_commands.add(new Load());
	executable_commands.add(new Select());
	executable_commands.add(new Print());
	executable_commands.add(new Save());
	executable_commands.add(new Add());
	executable_commands.add(new Update());
	executable_commands.add(new Swap());
	executable_commands.add(new Remove());
	executable_commands.add(new Equal());
	executable_commands.add(new Find());

	while (true)
	{
		cstring inp;
		cout << ">";
		cin >> inp;
		if (inp == "exit")
		{
			return;
		}
		bool is_command = false;
		for (unsigned int i = 0; i < executable_commands.count(); i++)
		{
			if (executable_commands[i]->get_trigger() == inp)
			{
				is_command = true;
				try
				{
					executable_commands[i]->execute(parsed, current);
					break;
				}
				catch (const std::exception& e)
				{
					cout << e.what();
				}
			}
		}
		if (!is_command)
		{
			cout << inp << " is not a command. Type \"help\" to view all available commands";
		}
		cout << endl;
	}

	// deallocate memory
	executable_commands.delete_all_content();
	if (parsed)
	{
		delete parsed;
	}
}

int main()
{
	run_demo();
	return 0;
}