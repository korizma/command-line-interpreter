#ifndef OPTIONTOKEN_H
#define OPTIONTOKEN_H
#include "token.hpp"

class OptionToken : public Token
{
    public:
        OptionToken(const std::string &token_value, int token_pos)
            : Token(token_value, token_pos)
        {
        }

        virtual TokenType type() const override
        {
            return Option;
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

        virtual void print() const override
        {
            std::cout << "OptionToken: " << value() << ", Position: " << pos() << std::endl;
        }
};

#endif
