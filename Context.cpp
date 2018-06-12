#include "Context.h"
#include <cstring>

using interpreters::Context;


Context::Context()
{
}

interpreters::Context::Context(const char * input, Component * output)
{
	this->setInput(input);
	this->setOutput(output);
}


Context::~Context()
{
	if (this->input)
	{
		delete[] this->input;
	}
	if (this->output)
	{
		delete[] this->output;
	}
}

void interpreters::Context::setOutput(Component * c)
{
	this->output = c;
}

void interpreters::Context::setInput(const char * input)
{
	this->inputLen = strlen(input);
	this->input = new char[this->inputLen + 1];
	for (size_t i = 0; i <= this->inputLen; i++)
	{
		this->input[i] = input[i];
	}
}

const char * interpreters::Context::getInput() const
{
	return this->input;
}

const Component * interpreters::Context::getOutput() const
{
	return this->output;
}
