#ifndef COMMANDTOKEN_H
#define COMMANDTOKEN_H
#include "token.hpp"

class CommandToken : public Token
{
    public:
        CommandToken(const std::string &token_value, int token_pos)
            : Token(token_value, token_pos)
        {
        }

        virtual TokenType type() const override
        {
            return CommandName;
        }

        virtual SubTokenType subType() const override
        {
            return SubTokenNone;
        }

        virtual std::vector<int> checkToken() const override
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

        virtual void print() const override
        {
            std::cout << "CommandToken: " << value() << ", Position: " << pos() << std::endl;
        }
};

#endif
