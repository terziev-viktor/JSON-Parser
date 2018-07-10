#pragma once
#include "ComponentFactory.h"

factory::ComponentFactory & factory::ComponentFactory::getFactory()
{
	static ComponentFactory theFactory;
	return theFactory;
}

void factory::ComponentFactory::registerCreator(const ComponentCreator * creator)
{
	if (this->index == this->max_creators_count)
	{
		this->expand();
	}
	this->creators[index] = creator;
	++index;
}

Component * factory::ComponentFactory::createFromTokens(TokensSimulator & tokens, unsigned int & line_number)
{
	Component * next = nullptr;
	for (int j = 0; j < this->index; j++)
	{
		next = this->creators[j]->createComponent(tokens, line_number);
		if (next)
		{
			return next;
		}
	}
	throw json_exception("Unknown json");
}

void factory::ComponentFactory::expand()
{
	this->max_creators_count *= 2;
	const ComponentCreator * * new_creators_buffer = new const ComponentCreator*[this->max_creators_count];
	for (int i = 0; i < this->index; i++)
	{
		new_creators_buffer[i] = this->creators[i];
	}
	delete this->creators;
	this->creators = new_creators_buffer;
}
