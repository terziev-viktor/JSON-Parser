#pragma once
#include "Component.h"
#include "ComponentFactory.h"
using components::Component;
#include <string>

Component::~Component()
{

}

Component * components::Component::operator->()
{
	return this;
}

Component & components::Component::operator*()
{
	return *this;
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

void components::ComponentCreator::skipWhitespace(Vector<Token>::Iterator & i, unsigned int & line_number) const
{
	while (i->getName() == TokenNames::Spacebar || i->getName() == TokenNames::Tab || i->getName() == TokenNames::NewLine)
	{
		if (i->getName() == NewLine)
		{
			++line_number;
		}
		++i;
	}
}

const Token & components::ComponentCreator::getBeginToken() const
{
	return this->begin;
}

const Token & components::ComponentCreator::getEndToken() const
{
	return this->end;
}
