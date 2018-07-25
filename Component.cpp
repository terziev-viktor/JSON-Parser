#pragma once
#include "Component.h"
#include "ComponentFactory.h"

components::creators::ComponentCreator::ComponentCreator()
{
	factory::ComponentFactory::getFactory().registerCreator(this);
}

components::Component::Component(const cstring & type)
{
	this->type = type;
}

cstring components::Component::tell_type() const
{
	return this->type;
}
