#pragma once
#include <stdexcept>
#include <iostream>
#include "cstring.h"
using tools::cstring;

namespace json_exceptions
{
	class json_exception : public std::exception
	{
	public:
		json_exception(const cstring & msg)
		{
			this->msg = msg;
		}

		virtual void log(std::ostream & os) const
		{
			os << msg << '\n';
		}

		const char * what() const
		{
			return this->msg.get_as_char_array();
			return nullptr;
		}
	private:
		cstring msg;
	};

	class bad_json_exception : public json_exception
	{
	public:
		bad_json_exception(const cstring & msg, const unsigned int line_number)
			:json_exception(msg)
		{
			this->line_number = line_number;
		}
		/*override*/
		void log(std::ostream & os) const
		{
			os << what() << " @ line number " << this->get_line_number() << '\n';
		}
		const unsigned int get_line_number() const
		{
			return line_number;
		}
	private:
		unsigned int line_number;
	};

	class invalid_key_name_exception : public json_exception
	{
	public:
		invalid_key_name_exception(const cstring & key_name)
			:json_exception("Invalid key name provided")		
		{
			//this->key_name = key_name;
		}
		/*override*/
		void log(std::ostream & os) const
		{
			os << what() << " " << this->get_key_name() << '\n';
		}
		const char * get_key_name() const
		{
			return this->key_name.get_as_char_array();
		}
	private:
		cstring key_name;
	};

	class bad_cast_exception : public json_exception
	{
	public:
		bad_cast_exception(const cstring & from, const cstring & to)
			:json_exception("Can't cast json object")
		{
			this->from = from;
			this->to = to;
		}
		/*override*/
		void log(std::ostream & os) const
		{
			os << what() << " from " << this->get_from() << " to " << this->get_to() << '\n';
		}
		const cstring & get_from() const
		{
			return this->from;
		}
		const cstring & get_to() const
		{
			return this->to;
		}
	private:
		cstring from;
		cstring to;
	};
}
