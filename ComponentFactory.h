#pragma once
#include "Component.h"
using components::Component;
using components::ComponentCreator;
#include "tools\List.hpp"
using tools::List;
#include "Tokenizer.h"

namespace factory
{
	class ComponentFactory
	{
	public:
		static ComponentFactory & getFactory();
		void registerCreator(const ComponentCreator * creator);
		List<Component> * createFromTokens(Vector<Token>::Iterator & i);
		Component * createNextFromTokens(Vector<Token>::Iterator & i);

	private:
		ComponentFactory():index(0){}
		~ComponentFactory(){}
		ComponentFactory(const ComponentCreator&);
		ComponentFactory & operator=(const ComponentFactory &) = default;
		
		const ComponentCreator* creators[10];
		int index;
	};

}
