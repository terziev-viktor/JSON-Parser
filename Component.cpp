#pragma once
#include "Component.h"
#include "ComponentFactory.h"

components::creators::ComponentCreator::ComponentCreator()
{
	factory::ComponentFactory::getFactory().registerCreator(this);
}
