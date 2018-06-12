#include "ComponentFactory.h"

factory::ComponentFactory & factory::ComponentFactory::getFactory()
{
	static ComponentFactory theFactory;
	return theFactory;
}

void factory::ComponentFactory::registerCreator(const ComponentCreator * creator)
{
	if (index < 10)
	{
		creators[index] = creator;
		++index;
	}
}

Component * factory::ComponentFactory::createByOpenTag(const char openTag, std::ifstream & in)
{
	for (int i = 0; i < index; i++)
	{
		if (creators[i]->getOpenTag() == openTag)
		{
			return creators[i]->createComponent(in);
		}
	}
	return nullptr;
}

Component * factory::ComponentFactory::create(const char * what, std::ifstream & in)
{
	for (int i = 0; i < index; i++)
	{
		if (strcmp(what, creators[i]->getName()) == 0)
		{
			return creators[i]->createComponent(in);
		}
	}
	return nullptr;
}
