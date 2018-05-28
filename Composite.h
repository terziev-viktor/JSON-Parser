#pragma once
#include "Component.h"
#include "tools/List.hpp"
using namespace tools;

namespace components
{
	// This is a components with children other components (Leafs ot Composites)
    class Composite : public Component
    {
    public:
		Composite();
    	~Composite();
    	void print() const;
    	const Component * getChild(int at) const;
    	void addChild(Component * child);
    private:
    	List<Component> children;
    };
}
