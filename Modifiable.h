#pragma once
#include "Component.h"

namespace components
{
	class Modifiable
	{
	public:
		virtual void add(unsigned int n, ...) = 0;

		virtual void update(const char * key, const char * json) = 0;
		virtual void update(int index, const char * json) = 0;
		virtual void update(int index, double number) = 0;
		virtual void update(const char * key, double number) = 0;
		virtual void update(const char * key, Component * new_value) = 0;
		virtual void update(int index, Component * new_value) = 0;

		virtual void remove(const char * key) = 0;
		virtual void remove(int index) = 0;

	};
}