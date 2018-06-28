#pragma once
#include "Modifiable.h"

namespace components
{
	class Indexable : public Component, public Modifiable
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

		virtual Indexable & operator=(const Indexable * other) = 0;
		virtual Indexable & operator=(const Indexable & other) = 0;
	};


}
