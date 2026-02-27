#include "optiontoken.hpp"
#include <iostream>

OptionToken::OptionToken(const std::string &token_value, int token_pos)
	: Token(token_value, token_pos)
{
}

TokenType OptionToken::type() const
{
	return Option;
}

SubTokenType OptionToken::subType() const
{
	return SubTokenNone;
}

std::vector<int> OptionToken::checkToken() const
{
	std::vector<int> errs;
	const std::string &val = value();
	int n = val.length();
	int start_pos = pos();
	// Options typically start with '-' and are alphanumeric after
	if (n < 2 || val[0] != '-')
	{
		errs.push_back(start_pos);
	}
	for (int i = 1; i < n && i < 8; ++i)
	{
		if (!std::isalnum(val[i]))
		{
			errs.push_back(start_pos + i);
		}
	}
	return errs;
}

void OptionToken::print() const
{
	std::cout << "OptionToken: " << value() << ", Position: " << pos() << std::endl;
}
