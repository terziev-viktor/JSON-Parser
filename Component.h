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

		virtual void print() const = 0;
		virtual void print(std::ostream & out) const = 0;
    };

	class ComponentCreator
	{
	public:
		ComponentCreator(Token begin, Token end);
		virtual ~ComponentCreator();

		virtual Component * createComponent(Vector<Token>::Iterator & i, unsigned int & line_number) const = 0;
		void skipWhitespace(Vector<Token>::Iterator & i, unsigned int & line_number) const;
		const Token & getBeginToken() const;
		const Token & getEndToken() const;
	protected:
		Token begin;
		Token end;

	};
} // components
