#include "commandtoken.hpp"
#include <iostream>

CommandToken::CommandToken(const std::string &token_value, int token_pos)
	: Token(token_value, token_pos)
{
}

TokenType CommandToken::type() const
{
	return CommandName;
}

SubTokenType CommandToken::subType() const
{
	return SubTokenNone;
}

std::vector<int> CommandToken::checkToken() const
{
	std::vector<int> errs;
	const std::string &val = value();
	int n = val.length();
	int start_pos = pos();
	// Command names must only contain letters
	for (int i = 1; i < n; ++i)
	{
		if (!std::isalpha(val[i]))
		{
			errs.push_back(start_pos + i);
		}
	}
	return errs;
}

void CommandToken::print() const
{
	std::cout << "CommandToken: " << value() << ", Position: " << pos() << std::endl;
}
