#pragma once

namespace tools
{
	template<class T>
	class DynamicArray
	{
	public:
		virtual void add(T * item) = 0;
		virtual T * getAt(unsigned int index) const = 0;
		virtual void removeAt(unsigned int index) = 0;
		virtual const bool isEmpty() const = 0;
		virtual void clear() = 0;
		virtual const unsigned int count() const = 0;
	};
}
// Interface for a dynamically allocated array of elements
