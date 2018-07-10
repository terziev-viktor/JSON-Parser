#pragma once
#include "JSONParser.h"
using interpreters::JSONParser;
namespace commands
{
	class Command
	{
	public:
		Command(const cstring & trigger);
		void set_trigger(const cstring & value);
		const cstring & get_trigger() const;
		virtual void execute(JSON * & parsed_json, JSON * & current) = 0;
	protected:
		Vector<cstring> read_args(const char * delim) const;
		cstring read_arg() const;
	private:
		cstring trigger;
	};
	class Help : public Command
	{
	public:
		Help() :Command("help") {}
		void execute(JSON * & parsed_json, JSON * & current);
	};

	class Load : public Command
	{
	public:
		Load() : Command("load"){}
		void execute(JSON * & parsed_json, JSON * & current);
	};

	class Select : public Command
	{
	public:
		Select() : Command("select"){}
		void execute(JSON * & parsed_json, JSON * & current);
	};

	class Print : public Command
	{
	public:
		Print() : Command("print"){}
		void execute(JSON * & parsed_json, JSON * & current);
	};

	class Save : public Command
	{
	public:
		Save():Command("save"){}
		void execute(JSON * & parsed_json, JSON * & current);
	};

	class Add : public Command
	{
	public:
		Add() : Command("add"){}
		void execute(JSON * & parsed_json, JSON * & current);
	};

	class Update : public Command
	{
	public:
		Update() :Command("update"){}
		void execute(JSON * & parsed_json, JSON * & current);
	};

	class Swap : public Command
	{
	public:
		Swap() :Command("swap"){}
		void execute(JSON * & parsed_json, JSON * & current);
	};

	class Remove : public Command
	{
	public:
		Remove() : Command("remove"){}
		void execute(JSON * & parsed_json, JSON * & current);
	};

	class Equal : public Command
	{
	public:
		Equal():Command("equal"){}
		void execute(JSON * & parsed_json, JSON * & current);
	};

	class Find : public Command
	{
	public:
		Find() :Command("find") { }
		void execute(JSON * & parsed_json, JSON * & current);
	private:
		void search(Vector<cstring> & keys_to_search);
	};
}
