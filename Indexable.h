#pragma once
#include "Modifiable.h"
#include "Component.h"
namespace components
{
	class Indexable : public Component, public Modifiable
	{
	public:
		virtual ~Indexable() = default;

		// Provodes access to elements of composite and array objects
		virtual Indexable & operator[](int index) = 0;
		virtual Indexable & operator[](const char * key) = 0;

		virtual const Indexable & operator[](const char * key) const = 0;
		virtual const Indexable & operator[](int index) const = 0;

		virtual Component & get(int index) = 0;
		virtual Component & get(const char * key) = 0;

		virtual const Component & get(int index) const = 0;
		virtual const Component & get(const char * key) const = 0;

		virtual Indexable & operator=(const Indexable & other) = 0;

		virtual Indexable & operator+=(const Indexable & other) = 0;
		
		// Returns whether an equal element is stored in the indexable object
		// out is a copy of that object (if it exists)
		virtual const bool contains(const char *, Component * out) const = 0;
	};

	Indexable & operator+(const Indexable & left, const Indexable & right);
}
