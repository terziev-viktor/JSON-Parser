#pragma once
#include "Component.h"
#include "ComponentFactory.h"
using components::Component;
#include <string>

Component::~Component()
{

}

components::ComponentCreator::ComponentCreator(Token begin, Token end)
{
	this->begin = begin;
	this->end = end;
	factory::ComponentFactory::getFactory().registerCreator(this);
}

components::ComponentCreator::~ComponentCreator()
{
}

const Token & components::ComponentCreator::getBeginToken() const
{
	return this->begin;
}

const Token & components::ComponentCreator::getEndToken() const
{
	return this->end;
}
