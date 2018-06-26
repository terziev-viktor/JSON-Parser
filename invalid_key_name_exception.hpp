#pragma once
#include "bad_json_exception.hpp"

namespace json_exceptions
{
	class invalid_key_name_exception : public bad_json_exception
	{
	public:
		invalid_key_name_exception(const unsigned int line_number)
			: bad_json_exception("Invalid key name for json object", line_number) 
		{
		}
		~invalid_key_name_exception();
	};

}

