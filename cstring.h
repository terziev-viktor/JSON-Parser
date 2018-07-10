#pragma once
#include "Vector.hpp"
namespace tools
{
	class cstring
	{
	public:
		cstring();
		// Init a cstring that can hold capacity characters
		cstring(unsigned int capacity);
		// value should be a string ending with '\0'
		cstring(const char * value);
		cstring(const cstring & other);
		~cstring();
		unsigned int get_length() const;
		unsigned int get_capacity() const;
		const char * get_as_char_array() const;
		cstring substring(unsigned int from, unsigned int to) const;
		int find_first_of(const cstring & characters, unsigned int start_from = 0) const;
		bool contains(const char ch) const;
		Vector<cstring> split(const cstring & delims) const;
		bool ends_with(const cstring &) const;
		bool starts_with(const char ch) const;
		bool to_int(int &) const;
		static cstring to_cstring(int num);
		/*operators*/
		cstring & operator+=(const cstring & other);
		cstring & operator+=(const char ch);
		cstring & operator=(const cstring & other);
		bool operator==(const cstring & other) const;
		bool operator!=(const cstring & other) const;
		char operator[](unsigned int index) const;
		char & operator[](unsigned int index);
	private:
		char * value;
		unsigned int length;
		unsigned int capacity;
	};

	cstring operator+(const cstring & a, const cstring & b);
	std::ostream & operator<<(std::ostream&, const cstring &);
	std::istream & operator>>(std::istream&, cstring & obj);
	
}

