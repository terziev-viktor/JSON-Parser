#include "ComponentFactory.h"
#include "json_exceptions.hpp"
using json_exceptions::bad_json_exception;

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
	unsigned int line_number = 1;
	while (!i.isDone())
	{
		ComponentCreator::skipWhitespace(i, line_number);
		unsigned int old = line_number;
		Component * next = ComponentFactory::getFactory().createNextFromTokens(i, line_number);
		if (next != nullptr)
		{
			result->add(next);
		}
		++i;
	}
	return result;
}

Component * factory::ComponentFactory::createNextFromTokens(Vector<Token>::Iterator & i, unsigned int & line_number)
{
	Component * next = nullptr;
	for (size_t j = 0; j < this->index; j++)
	{
		if (this->creators[j]->getBeginToken().getName() == i->getName())
		{
			next = this->creators[j]->createComponent(i, line_number);

			if (this->creators[j]->getEndToken().getName() != i->getName())
			{
				throw bad_json_exception("Unexpected token", line_number);
			}
			return next;
		}
	}
	return nullptr;
}
