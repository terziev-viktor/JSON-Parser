#pragma once
#include "JSONParser.h"
#include <fstream>
#include "json_exceptions.hpp"
#include "ComponentFactory.h"
using factory::ComponentFactory;
using namespace json_exceptions;
using std::ifstream;
using namespace interpreters;

bool interpreters::JSONParser::file_exists(const cstring & path)
{
	std::ifstream f;
	f.open(path.get_as_char_array());
	return f.good();
}

Component * interpreters::JSONParser::parse(const cstring & json)
{
	if (json.get_length() == 0)
	{
		return nullptr;
	}
	TokensSimulator tokens(json);
	unsigned int line = 1;
	line += tokens.skip_whitespace();
	Component * p = ComponentFactory::getFactory().createFromTokens(tokens, line);
	return p;
}

components::Array * interpreters::JSONParser::parse_json_array(const cstring & json)
{
	TokensSimulator tokens(json);
	unsigned int line = 1;
	line += tokens.skip_whitespace();
	Array * p = ArrayCreator::create_array(tokens, line);
	if (p)
	{
		line += tokens.skip_whitespace();
		if (!tokens.is_done())
		{
			throw bad_json_exception("End of string/file expected", line);
		}
		return p;
	}
	return nullptr;
}

Composite * interpreters::JSONParser::parse_json(const cstring & json)
{
	TokensSimulator tokens(json);
	unsigned int line = 1;
	line += tokens.skip_whitespace();
	Composite * p = CompositeCreator::create_json(tokens, line);
	if (p)
	{
		line += tokens.skip_whitespace();
		if (!tokens.is_done())
		{
			throw bad_json_exception("End of string/file expected", line);
		}
		return p;
	}
	return nullptr;
}

JSON & interpreters::JSONParser::parse_file(const cstring & path)
{
	if (!JSONParser::file_exists(path))
	{
		throw json_exception("Json file does not exist");
	}
	if (!path.ends_with(".json"))
	{
		throw json_exception("File is not a .json file");
	}
	std::ifstream in;
	in.open(path.get_as_char_array());
	if (!in)
	{
		throw json_exception("Could not open json file");
	}
	char buffer[1024];
	cstring file;
	while (in)
	{
		in.read(buffer, 1021);
		int count = in.gcount();
		buffer[count] = '\0';
		file += buffer;
	}
	std::cout << file << std::endl;
	Component * parsed = JSONParser::parse(file);
	JSON * casted = dynamic_cast<JSON *>(parsed);
	if (!casted)
	{
		throw json_exception("Json file does not contain an Indexable object");
	}
	return *casted;
}
