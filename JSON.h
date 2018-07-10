#pragma once
#include "Component.h"
#include "String.h"
namespace components
{
	class JSON : public Component
	{
	public:
		virtual ~JSON() = default;

		virtual JSON & get(const String & index) = 0;
		virtual const JSON & get(const String & index) const = 0;

		virtual void update(const String&, const Component & value) = 0;
		virtual void remove(const String&) = 0;
		virtual void swap(const String&, const String&) = 0;
		virtual void add(unsigned int count, ...) = 0;
	};
}
