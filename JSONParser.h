#pragma once
#include "Array.h"
#include "Composite.h"
using components::creators::CompositeCreator;
using components::creators::ArrayCreator;
using namespace components;
using namespace tools;
using namespace components;

namespace interpreters
{
	class JSONParser
	{
	public:
		// Parses the string to json
		// Returns true on at least one successful parsing
		static Component * parse(const cstring & json);
		static Array * parse_json_array(const cstring & json);
		static Composite * parse_json(const cstring & json);
		static JSON & parse_file(const cstring & path);
		static bool file_exists(const cstring & path);
	};
}

