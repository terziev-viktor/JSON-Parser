#pragma once
#include <iostream>
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
		ComponentCreator(char openTag, char closeTag, const char * name);
		virtual ~ComponentCreator();

		virtual Component * createComponent(std::ifstream & in) const = 0;
		const char getOpenTag() const;
		const char getClosingTag() const;
		const char * getName() const;
	protected:
		char openTag;
		char closeTag;
		static const int MAX_NAME_LEN = 100;
		char name[MAX_NAME_LEN];
	};
} // components
