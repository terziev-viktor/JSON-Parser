#include "Boolean.h"
using components::Boolean;
using components::Component;
using components::creators::BooleanCreator;

static const BooleanCreator theBooleanCreator;

components::Boolean::Boolean()
	:value(false)
{
}

components::Boolean::Boolean(bool v)
{
	this->value = v;
}

components::Boolean::operator bool() const
{
	this->value;
}

bool components::Boolean::operator!() const
{
	return !(bool)(*this);
}

bool components::Boolean::operator==(const Boolean & other) const
{
	return this->value == other.value;
}

void components::Boolean::print(std::ostream & out, bool pretty, unsigned int tab_index) const
{
	if (pretty)
	{
		out << (this->value ? "True" : "False");
	}
	else
	{
		out << this->value;
	}
}

Component * Boolean::copy() const
{
	return new Boolean(*this);
}

bool components::Boolean::equals(const Component & other) const
{
	try
	{
		const Boolean & casted = dynamic_cast<const Boolean &>(other);
		return *this == casted;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

cstring components::Boolean::tell_type() const
{
	return "Boolean";
}

Component * components::creators::BooleanCreator::createComponent(TokensSimulator & tokens, unsigned int & line) const
{
	cstring a("True");
	tokens.save_pos();
	bool yes = true;
	for (unsigned int i = 0; i < a.get_length(); i++)
	{
		if (a[i] != tokens.get_next())
		{
			yes = false;
			break;
		}
	}
	if (yes)
	{
		return new Boolean(true);
	}
	a = "False";
	yes = true;
	tokens.revert();
	for (unsigned int i = 0; i < a.get_length(); i++)
	{
		if (a[i] != tokens.get_next())
		{
			yes = false;
			break;
		}
	}
	if (yes)
	{
		return new Boolean(false);
	}
	tokens.revert();
	return nullptr;
}
