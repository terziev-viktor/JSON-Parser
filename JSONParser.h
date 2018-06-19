#pragma once
#include "tools\List.hpp"
#include "Component.h"
#include "String.h"

using namespace tools;
using namespace components;

namespace interpreters
{
	class JSONParser
	{
	public:
		JSONParser();
		JSONParser(DynamicArray<Component> * list, const char * path);

		~JSONParser();
		bool load(const char * path);
		const Component * get(unsigned int index) const;
		void add(Component * component);
		void print() const;
		const String & getFile() const;
	private:
		DynamicArray<Component> * list;
		String file;
	};
}

