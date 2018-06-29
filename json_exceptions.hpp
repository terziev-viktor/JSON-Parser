#pragma once
#include <stdexcept>

namespace json_exceptions
{
	class json_exception : public std::exception
	{
	public:
		json_exception(const char * msg)
		{
			strcpy_s(this->msg, sizeof(this->msg), msg);
		}

		virtual void log(std::ostream & os) const
		{
			os << msg << '\n';
		}

		const char * what() const
		{
			return this->msg;
		}
	private:
		char msg[50];
	};

	class bad_json_exception : public json_exception
	{
	public:
		bad_json_exception(const char * msg, const unsigned int line_number)
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
		invalid_key_name_exception(const char * key_name)
			:json_exception("Invalid key name provided")		
		{
			strcpy_s(this->key_name, sizeof(this->key_name), key_name);
		}
		/*override*/
		void log(std::ostream & os) const
		{
			os << what() << " " << this->get_key_name() << '\n';
		}
		const char * get_key_name() const
		{
			return this->key_name;
		}
	private:
		char key_name[50];
	};

	class bad_cast_exception : public json_exception
	{
	public:
		bad_cast_exception(const char * from, const char * to)
			:json_exception("Can't cast json object")
		{
			this->setFrom(from);
			this->setTo(to);
		}
		/*override*/
		void log(std::ostream & os) const
		{
			os << what() << " from " << this->get_from() << " to " << this->get_to() << '\n';
		}
		const char * get_from() const
		{
			return this->from;
		}
		const char * get_to() const
		{
			return this->to;
		}
	private:
		void setFrom(const char * from)
		{
			strcpy_s(this->from, sizeof(this->from), from);
		}
		void setTo(const char * to)
		{
			strcpy_s(this->to, sizeof(this->to), to);
		}
		char from[20];
		char to[20];
	};
}
