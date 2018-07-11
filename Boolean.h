#pragma once
#include "Component.h"
namespace components
{
	class Boolean : public Component
	{
	public:
		Boolean();
		Boolean(bool v);

		bool operator==(const Boolean & other) const;
		/*override*/
		void print(std::ostream & out, bool pretty, unsigned int tab_index) const;
		Component * copy() const;
		bool equals(const Component & other) const;
		cstring tell_type() const;
	private:
		bool value;
	};

	namespace creators
	{
		class BooleanCreator : public ComponentCreator
		{
		public:
			Component * createComponent(TokensSimulator & tokens, unsigned int & line_number) const;
		};
	}
}
