#pragma once
#include "tools\PointerContainer.hpp"
using tools::PointerContainer;
#include "JSON.h"
namespace components
{
	class Array : public JSON
	{
	public:
		Array();
		~Array();
		void add(const Component&);
		unsigned int count() const;
		void clear();
		bool is_empty() const;
		int index_of(const Component & other) const;

		Array & operator=(const Array & other);
		Array & operator+=(const Array & other);
		Array & operator-=(unsigned int index);
		bool operator==(const Array & other) const;
		bool operator!=(const Array & other) const;
		Component & operator[](unsigned int index);
		const Component & operator[](unsigned int index) const;
		operator bool() const;
		bool operator!() const;
		/*override JSON*/
		JSON & get(const String & index);
		const JSON & get(const String & index) const;
		void update(const String&, const Component & new_value);
		void remove(const String&);
		void swap(const String& str1, const String& str2);
		void components::Array::add(unsigned int items_count, ...);

		/*override component*/
		Component * copy() const;
		void print(std::ostream & out, bool pretty, unsigned int tab_index) const;
		bool equals(const Component & other) const;
	private:
		PointerContainer<Component> values;
	};

	namespace creators
	{
		class ArrayCreator :public ComponentCreator
		{
		public:
			Component * createComponent(TokensSimulator & tokens, unsigned int & line_number) const;

			static Array * create_array(TokensSimulator & tokens, unsigned int & line_number);
		};
	}
}
