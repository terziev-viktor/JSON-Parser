#pragma once
#include "TokensSimulator.h"
#include "cstring.h"
#include "json_exceptions.hpp"
using namespace json_exceptions;
using tools::cstring;
using tools::TokensSimulator;

namespace components
{
	// This class represents the abstraction of different json components
	class Component
	{
	public:
		Component(const cstring & type);

		virtual ~Component() = default;
		// Print on a given output stream <out>
		// <tab_index> is used to print the object in a pretty way
		// <pretty> determines whether to print pretty(true) or minified(false)
		virtual void print(std::ostream & out, bool pretty, unsigned int tab_index) const = 0;

		virtual Component * copy() const = 0;

		virtual bool equals(const Component & other) const = 0;

		cstring tell_type() const;
	private:
		cstring type;
	};
	namespace creators
	{
		class ComponentCreator
		{
		public:
			ComponentCreator();
			virtual ~ComponentCreator() = default;

			virtual Component * createComponent(TokensSimulator & tokens, unsigned int & line_number) const = 0;
		};
	}
} // components
