#pragma once
#include "tools\List.hpp"
#include "Component.h"
using namespace tools;
using namespace components;

namespace interpreters
{
	class JSONParser
	{
	public:
		JSONParser(const char * path);
		JSONParser(DynamicArray<Component> * list, const char * path);

		~JSONParser();

		const Component * get(unsigned int index) const;
		void add(Component * component);
		void print() const;
	private:
		DynamicArray<Component> * list;

		void load(const char * path);
	};
}

