#pragma once
#include "Component.h"

namespace components
{
	class Indexable : public Component
	{
	public:
		virtual ~Indexable() = default;

		virtual Indexable & operator[](int index) = 0;
		virtual Indexable & operator[](const char * key) = 0;

		virtual const Indexable & operator[](const char * key) const = 0;
		virtual const Indexable & operator[](int index) const = 0;

		virtual Component & get(int index) = 0;
		virtual Component & get(const char * key) = 0;

		virtual const Component & get(int index) const = 0;
		virtual const Component & get(const char * key) const = 0;

		virtual void update(const char * key, const char * json) = 0;
		virtual void update(int index, const char * json) = 0;
		virtual void update(int index, double number) = 0;
		virtual void update(const char * key, double number) = 0;
		virtual void update(const char * key, Component * new_value) = 0;
		virtual void update(int index, Component * new_value) = 0;
	};


}
