#pragma once
#include "Component.h"
using components::Component;

namespace interpreters
{
	class Context
	{
	public:
		Context();
		Context(const char * input, Component * output);
		~Context();
		void setOutput(Component * c);
		void setInput(const char * input);
		const char * getInput() const;
		const Component * getOutput() const;
	private:
		char * input;
		size_t inputLen;
		Component * output;
	};
}
