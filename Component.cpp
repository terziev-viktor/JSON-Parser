#pragma once
#include "Component.h"
#include "ComponentFactory.h"
using components::Component;
#include <string>

Component::~Component()
{

}

components::ComponentCreator::ComponentCreator(const char * name)
{
	strcpy(this->name, name);
	factory::ComponentFactory::getFactory().registerCreator(this);
}

components::ComponentCreator::~ComponentCreator()
{
}

const char * components::ComponentCreator::getName() const
{
	return this->name;
}
