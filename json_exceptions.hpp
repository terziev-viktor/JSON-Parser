#pragma once
#include <stdexcept>

namespace json_exceptions
{
	class bad_json_exception : public std::exception
	{
	public:
		bad_json_exception(const char * msg, const unsigned int line_number)
		{
			this->line_number = line_number;
			strcpy_s(this->msg, sizeof(this->msg), msg);
		}

		const char * what() const
		{
			return this->msg;
		}

		const unsigned int get_line_number() const
		{
			return line_number;
		}
	private:
		char msg[50];
		unsigned int line_number;
	};

	class invalid_key_name_exception : public std::exception
	{
	public:
		invalid_key_name_exception(const char * key_name)
		{
			strcpy_s(this->key_name, sizeof(this->key_name), key_name);
		}
		const char * what() const
		{
			return "Invalid key name for json object";
		}
		const char * get_key_name() const
		{
			return this->key_name;
		}
	private:
		char key_name[50];
	};
}
