#pragma once
#include "String.h"
#include "Vector.hpp"
using tools::Vector;
using components::String;

enum TokenNames 
{
	ObjectBegin = 0,
	ObjectEnd,
	KeyBegin,
	KeyEnd,
	KeyValSeparator,
	StringBegin,
	StringEnd,
	StringOrNumber,
	ArrayBegin,
	ArrayEnd,
	Comma,
	DoubleQuote,
	SingleQuote,
	Spacebar,
	Tab,
	NewLine,
	EndOfString, // the \0 symbol
	Unknown
};

class Token
{
public:
	Token();
	~Token();
	Token(TokenNames name, const char * value);
	Token(TokenNames name, const char ch);
	Token(TokenNames name, const String & value);
	const TokenNames getName() const;
	const String & getValue() const;
	void setName(TokenNames name);
	void setValue(const char * value);
	void setValue(const String & value);

	// operators
	Token & operator=(const Token & other);
private:
	TokenNames name;
	String value;
};

std::ostream & operator<<(std::ostream & os, const Token & t);

class Tokenizer
{
public:
	static Vector<Token> tokenize(const String & str);
private:
	Tokenizer();
};

