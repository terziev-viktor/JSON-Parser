#pragma once
#include "tools\List.hpp"
#include "Component.h"
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
		bool load(const char * path);
		const Component * get(unsigned int index) const;
		void add(Component * component);
		void print() const;
		const string & getFile() const;
	private:
		List<Component> * list;
		string file;
	};
}

