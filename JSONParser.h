#pragma once
#include "tools\List.hpp"
#include "Composite.h"
#include "Array.h"
using components::Array;
using components::Composite;

#include <string>
using std::string;

using namespace tools;
using namespace components;

namespace interpreters
{
	class JSONParser
	{
	public:
		JSONParser();
		
		~JSONParser();
		// Parses the string to json
		// Returns true on at least one successful parsing
		bool parse(const std::string & json);
		bool parse(const char * json);
		bool parse();

		// Loads a file for parsing
		bool load(const char * path);
		// Saves all parsed json objects to a file
		bool save(const char * path, bool overrideFile = true, bool pretty = true);

		// Finds all keys in json objects and all strings or numbers in arrays
		// returns array of their values
		Array * findAll(const char * key);

		// getters
		const Component * get(unsigned int index) const;
		Component * get(unsigned int index);
		Composite * getAsJsonObject(unsigned int index);
		const Composite * getAsJsonObject(unsigned int index) const;
		Array * getAsJsonArray(unsigned int index);
		const Array * getAsJsonArray(unsigned int index) const;
		const Component & operator[](unsigned int index) const;
		Component & operator[](unsigned int index);

		// Count of currently parsed elements
		const unsigned int getParsedCount() const;
		void add(Component * component);
		void print() const;
		const string & getFile() const;
	private:
		List<Component> * list;
		string file;
		bool fileLoaded;
		bool fileExists(const char * path);
	};
}

