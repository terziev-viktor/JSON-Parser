#pragma once
#include "cstring.h"
namespace tools
{
	// Simulates a token stream using a cstring object
	class TokensSimulator
	{
	public:
		TokensSimulator(const cstring &);
		// Gets the current token in the stream. Doesn not set the next one.
		char get() const;
		// returns the current token and sets the next one.
		char get_next();
		// sets the next token.
		void next();
		// cheks if there are more tokens to get.
		bool is_done() const;
		// skip until given tokens, returns number of skipped tokens
		int skip_until(const cstring & tokens);
		// skips whitespace tokens, returns number of newlines skipped
		int skip_whitespace();
		// sets current token as previous token
		void prev();
		// revert n steps
		void prev(int);
		// saves the current position
		void save_pos();
		// revert to last saved position
		void revert();
	private:
		cstring tokens_str;
		int pos;
		int save;
	};
}


