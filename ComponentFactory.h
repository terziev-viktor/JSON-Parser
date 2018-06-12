#pragma once
#include "Component.h"
using components::Component;
using components::ComponentCreator;

namespace factory
{
	class ComponentFactory
	{
	public:
		static ComponentFactory & getFactory();
		void registerCreator(const ComponentCreator * creator);
		Component * createByOpenTag(const char openTag, std::ifstream & in);
		Component * create(const char * what, std::ifstream & in);

	private:
		ComponentFactory():index(0){}
		~ComponentFactory(){}
		ComponentFactory(const ComponentCreator&);
		ComponentFactory & operator=(const ComponentFactory &) = default;
		
		const ComponentCreator* creators[10];
		int index;
	};

}
