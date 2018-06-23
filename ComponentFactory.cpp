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

List<Component> * factory::ComponentFactory::createFromTokens(Vector<Token>::Iterator & i)
{
	List<Component> * result = new List<Component>();
	while (!i.isDone())
	{
		Component * next = ComponentFactory::getFactory().createNextFromTokens(i);
		if (next != nullptr)
		{
			result->add(next);
		}
		++i;
	}
	return result;
}

Component * factory::ComponentFactory::createNextFromTokens(Vector<Token>::Iterator & i)
{
	Component * next = nullptr;
	for (size_t j = 0; j < this->index; j++)
	{
		if (this->creators[j]->getBeginToken().getName() == i->getName())
		{
			next = this->creators[j]->createComponent(i);
			//next->print();
			if (this->creators[j]->getEndToken().getName() != i->getName())
			{
				cout << "Expected " << this->creators[j]->getEndToken().getName() << endl;
			}
			return next;
		}
	}
	return nullptr;
}
