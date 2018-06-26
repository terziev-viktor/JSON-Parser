#include "Tokenizer.h"

Vector<Token> Tokenizer::tokenize(const string & str)
{
	Vector<Token> tokens;
	bool EndOfStringReached = false;
	for (size_t i = 0; !EndOfStringReached && i < str.length(); ++i)
	{
		char current = str[i];
		switch (current)
		{
		case '{':
		{
			Token t(TokenNames::ObjectBegin, '{');
			tokens.add(t);
			break;
		}
		case '}':
		{
			Token t(TokenNames::ObjectEnd, '{');
			tokens.add(t);
			break;
		}
		case '[':
		{
			Token t(TokenNames::ArrayBegin, '[');
			tokens.add(t);
			break;
		}
		case ']':
		{
			Token t(TokenNames::ArrayEnd, ']');
			tokens.add(t);
			break;
		}
		case ',':
		{
			Token t(TokenNames::Comma, ',');
			tokens.add(t);
			break;
		}
		case ':':
		{
			Token t(TokenNames::KeyValSeparator, ':');
			tokens.add(t);
			break;
		}
		case '"':
		{
			Token t(TokenNames::DoubleQuote, '"');
			tokens.add(t);
			break;
		}
		case '\'':
		{
			Token t(TokenNames::SingleQuote, '\'');
			tokens.add(t);
			break;
		}
		case ' ':
		{
			Token t(TokenNames::Spacebar, ' ');
			tokens.add(t);
			break;
		}
		case '\t':
		{
			Token t(TokenNames::Tab, '\t');
			tokens.add(t);
			break;
		}
		case '\n':
		{
			Token t(TokenNames::NewLine, '\n');
			tokens.add(t);
			break;
		}
		case '\0':
		{
			Token t(TokenNames::EndOfString, '\0');
			tokens.add(t);
			EndOfStringReached = true;
			break;
		}
		default:
		{
			int to = str.find_first_of("]},\"\0", i);
			if (to == -1)
			{
				Token t(TokenNames::Unknown, '0');
				tokens.add(t);
				break;
			}
			string stringValue = str.substr(i, to - i);
			i = to - 1;
			Token t(TokenNames::StringOrNumber, stringValue);
			tokens.add(t);
			break;
		}
		}
	}
	return tokens;
}

Vector<Token> Tokenizer::tokenize(const char * str)
{
	std::string s(str);
	return Tokenizer::tokenize(s);
}

Tokenizer::Tokenizer()
{
}

Token::Token()
{
}

Token::~Token()
{

}

Token::Token(TokenNames name, const char * value)
{
	this->setName(name);
	this->setValue(value);
}

Token::Token(TokenNames name, const char ch)
{
	this->name = name;
	this->value = ch;
}

Token::Token(TokenNames name, const string & value)
{
	this->setName(name);
	this->setValue(value);
}

const TokenNames Token::getName() const
{
	return this->name;
}

const string & Token::getValue() const
{
	return this->value;
}

void Token::setName(TokenNames name)
{
	this->name = name;
}

void Token::setValue(const char * value)
{
	this->value = value;
}

void Token::setValue(const string & value)
{
	this->value = value;
}

Token & Token::operator=(const Token & other)
{
	this->setName(other.getName());
	this->setValue(other.getValue());
	return *this;
}

std::ostream & operator<<(std::ostream & os, const Token & t)
{
	os << t.getName() << " : " << t.getValue();
	return os;
}
