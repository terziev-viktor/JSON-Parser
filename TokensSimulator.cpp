#include "TokensSimulator.h"

tools::TokensSimulator::TokensSimulator(const cstring & str)
	:pos(0),save(0)
{
	this->tokens_str = str;
}

char tools::TokensSimulator::get() const
{
	return this->tokens_str[this->pos];
}

char tools::TokensSimulator::get_next()
{
	char ch = this->tokens_str[this->pos];
	this->next();
	return ch;
}

void tools::TokensSimulator::next()
{
	if (this->pos < this->tokens_str.get_length())
	{
		++this->pos;
	}
}

bool tools::TokensSimulator::is_done() const
{
	return this->pos == (this->tokens_str.get_length());
}

int tools::TokensSimulator::skip_until(const cstring & tokens)
{
	int skipped = 0;
	while (!this->is_done() && !tokens.contains(this->tokens_str[this->pos]))
	{
		this->next();
		++skipped;
	}
	if (this->is_done())
	{
		return -1;
	}
	return skipped;
}

int tools::TokensSimulator::skip_whitespace()
{
	int newlines = 0;
	while (this->pos < this->tokens_str.get_length() &&
		(this->tokens_str[this->pos] == '\n' ||
		this->tokens_str[this->pos] == '\t' ||
		this->tokens_str[this->pos] == ' '))
	{
		if (this->tokens_str[this->pos] == '\n')
		{
			++newlines;
		}
		++this->pos;
	}
	return newlines;
}

void tools::TokensSimulator::prev()
{
	if (this->pos > 0)
	{
		--this->pos;
	}
}

void tools::TokensSimulator::prev(int num)
{
	if (num > this->pos)
	{
		this->pos = 0;
		return;
	}
	this->pos -= num;
}

void tools::TokensSimulator::save_pos()
{
	this->save = this->pos;
}

void tools::TokensSimulator::revert()
{
	this->pos = this->save;
}
