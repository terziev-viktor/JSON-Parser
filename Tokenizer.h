#pragma once
#include <string>
using std::string;
#include "json_exceptions.hpp"
using json_exceptions::json_exception;
#include "Vector.hpp"
using tools::Vector;

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
	Token(const Token & other);
	~Token();
	Token(TokenNames name, const char * value);
	Token(TokenNames name, const char ch);
	Token(TokenNames name, const string & value);
	const TokenNames getName() const;
	const string & getValue() const;
	void setName(TokenNames name);
	void setValue(const char * value);
	void setValue(const string & value);

	// operators
	Token & operator=(const Token & other);
private:
	TokenNames name;
	string value;
};

std::ostream & operator<<(std::ostream & os, const Token & t);

class Tokenizer
{
public:
	static Vector<Token> tokenize(const string & str);
	static Vector<Token> tokenize(const char * str);
private:
	Tokenizer();
};

