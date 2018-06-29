#include "Commands.h"
using namespace commands;
using std::cin;
using std::cout;
using std::endl;
// This is a .NET solution
// I'm using the Composite OOP Design Pattern
// Source::https://www.oodesign.com/composite-pattern.html
// Abstract Factory OOP Design Pattern
// Source::https://learn.fmi.uni-sofia.bg/mod/folder/view.php?id=100016

void run_demo()
{
	JSONParser parser;
	Indexable * current = nullptr;
	List <Command> executable_commands;
	executable_commands.add(new Help());
	executable_commands.add(new Load());
	executable_commands.add(new Select());
	executable_commands.add(new Print());
	executable_commands.add(new Save());
	executable_commands.add(new ArrayAdd());
	executable_commands.add(new JsonAdd());
	executable_commands.add(new Update());
	executable_commands.add(new Swap());
	executable_commands.add(new Remove());

	while (true)
	{
		try
		{
			char inp[20];
			cout << ">";
			cin >> inp;
			cin.ignore();
			if (strcmp(inp, "exit") == 0)
			{
				return;
			}
			for (size_t i = 0; i < executable_commands.count(); i++)
			{
				if (executable_commands.getAt(i)->getTrigger() == inp)
				{
					executable_commands.getAt(i)->execute(current, parser);
					break;
				}
			}
			cout << endl;
		}
		catch (const json_exception& e)
		{
			e.log(cout);
		}
	}
}

int main()
{
	run_demo();
	return 0;
}