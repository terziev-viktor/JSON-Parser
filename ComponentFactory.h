#pragma once
#include "Component.h"
using components::Component;
using components::creators::ComponentCreator;
namespace factory
{
	class ComponentFactory
	{
	public:
		static ComponentFactory & getFactory();
		void registerCreator(const ComponentCreator * creator);
		Component * createFromTokens(TokensSimulator & tokens, unsigned int & line_number);
		static const unsigned int INIT_CREATORS_COUNT = 15;
	private:
		ComponentFactory() :index(0), max_creators_count(INIT_CREATORS_COUNT)
		{
			this->creators = new const ComponentCreator*[this->max_creators_count];
		}
		~ComponentFactory() 
		{
			delete[] this->creators;
		}
		ComponentFactory(const ComponentCreator&);
		const ComponentCreator * * creators = nullptr;
		int index;
		unsigned int max_creators_count;
		void expand();
	};

}
