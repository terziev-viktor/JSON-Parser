#pragma once

namespace components
{
    // This class represents the abstraction of different json parts (key-value-pairs, composite objects)
    class Component
    {
    public:
    	virtual ~Component();

    	virtual void print() const = 0;
    };
} // components
