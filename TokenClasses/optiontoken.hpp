#ifndef OPTIONTOKEN_H
#define OPTIONTOKEN_H
#include "token.hpp"

class OptionToken : public Token
{
    public:
    OptionToken(const std::string &token_value, int token_pos);
    virtual TokenType type() const override;
    virtual SubTokenType subType() const override;
    virtual std::vector<int> checkToken() const override;
    virtual void print() const override;
};

#endif
