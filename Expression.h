#pragma once
#include "Context.h"

namespace interpreters
{
	class Expression
	{
	public:
		Expression();
		~Expression();
		void interpret(Context & c);
	};
}

