#pragma once
#include "Component.h"
#include "tools/List.hpp"
using namespace tools;
//using factory::ComponentCreator;

namespace components
{
	// This is a components with children other components (Leafs ot Composites)
    class Composite : public Component
    {
    public:
		Composite();
    	~Composite();
		void print() const;
		void print(std::ostream & out) const;
    	const Component * getChild(int at) const;
    	void addChild(Component * child);
    private:
    	List<Component> children;
    };

	class CompositeCreator : public ComponentCreator
	{
	public:
		CompositeCreator();
		Component * createComponent(std::ifstream & in) const;
	};

	static CompositeCreator theCompositeCreator;
}
