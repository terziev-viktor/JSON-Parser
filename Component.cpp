#pragma once
#include "Component.h"
#include "ComponentFactory.h"
using components::Component;
#include <string>

Component::~Component()
{

}

components::ComponentCreator::ComponentCreator(char openTag, char closeTag, const char * name)
	:openTag(openTag), closeTag(closeTag)
{
	strcpy(this->name, name);
	factory::ComponentFactory::getFactory().registerCreator(this);
}

components::ComponentCreator::~ComponentCreator()
{
}

const char components::ComponentCreator::getOpenTag() const
{
	return openTag;
}

const char components::ComponentCreator::getClosingTag() const
{
	return closeTag;
}

const char * components::ComponentCreator::getName() const
{
	return this->name;
}
