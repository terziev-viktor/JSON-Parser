#pragma once
#include <stdexcept>

namespace json_exceptions
{
	class bad_json_exception : public std::exception
	{
	public:
		bad_json_exception(const char * msg, const unsigned int & line_number)
		{
			this->line_number = line_number;
			strcpy_s(this->msg, sizeof(this->msg), msg);
		}

		const char * what() const
		{
			return this->msg;
		}

		const unsigned int getLineNumber() const
		{
			return line_number;
		}
	private:
		char msg[50];
		unsigned int line_number;
	};
}
