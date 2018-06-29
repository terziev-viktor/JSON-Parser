#include "Indexable.h"

components::Indexable & components::operator+(const Indexable & left, const Indexable & right)
{
	Component * cpy = left.copy();
	*cpy += right;
	return dynamic_cast<Indexable &>(*cpy);
}
