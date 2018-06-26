#pragma once
#include <iostream>
#include "Tokenizer.h"

namespace components
{
    // This class represents the abstraction of different json parts (key-value-pairs, composite objects)
    class Component
    {
    public:
    	virtual ~Component();

		virtual void print(unsigned short tab_index = 0, bool pretty = true) const = 0;
		virtual void print(std::ostream & out, unsigned short tab_index = 0, bool pretty = true) const = 0;
		virtual bool operator==(const Component * other) const = 0;
		virtual bool operator==(const Component & other) const = 0;
		virtual Component & operator=(Component * other) = 0;
    };

	class ComponentCreator
	{
	public:
		ComponentCreator(Token begin, Token end);
		virtual ~ComponentCreator();

		virtual Component * createComponent(Vector<Token>::Iterator & i, unsigned int & line_number) const = 0;
		static void skipWhitespace(Vector<Token>::Iterator & i, unsigned int & line_number);
		const Token & getBeginToken() const;
		const Token & getEndToken() const;
	protected:
		Token begin;
		Token end;

	};
} // components
