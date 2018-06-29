#pragma once
#include "String.h"
#include "JSONParser.h"
using namespace interpreters;
using components::String;

namespace commands
{
	class Command
	{
	public:
		Command();
		Command(const char * trigger);
		~Command();
		void setTrigger(const char * value);
		void setTrigger(const String & value);
		const String & getTrigger() const;
		virtual void execute(Indexable *& current, JSONParser & parser) = 0;
	protected:
		Vector<String> readArgs(char delim) const;
		String readArg() const;
	private:
		String trigger;
	};
	class Help : public Command
	{
	public:
		Help() :Command("help") {}
		void execute(Indexable *& current, JSONParser & parser);
	};

	class Load : public Command
	{
	public:
		Load() : Command("load"){}
		void execute(Indexable *& current, JSONParser & parser);
	};

	class Select : public Command
	{
	public:
		Select() : Command("select"){}
		void execute(Indexable *& current, JSONParser & parser);
	};

	class Print : public Command
	{
	public:
		Print() : Command("print"){}
		void execute(Indexable *& current, JSONParser & parser);
	};

	class Save : public Command
	{
	public:
		Save():Command("save"){}
		void execute(Indexable *& current, JSONParser & parser);
	};

	class ArrayAdd : public Command
	{
	public:
		ArrayAdd() : Command("array_add"){}
		void execute(Indexable *& current, JSONParser & parser);
	};

	class JsonAdd : public Command
	{
	public:
		JsonAdd() : Command("json_add"){}
		void execute(Indexable *& current, JSONParser & parser);
	};

	class Update : public Command
	{
	public:
		Update() :Command("update"){}
		void execute(Indexable *& current, JSONParser & parser);
	};

	class Swap : public Command
	{
	public:
		Swap() :Command("swap"){}
		void execute(Indexable *& current, JSONParser & parser);
	};

	class Remove : public Command
	{
	public:
		Remove() : Command("remove"){}
		void execute(Indexable *& current, JSONParser & parser);
	};
}
