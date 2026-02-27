#ifndef COMMANDTOKEN_H
#define COMMANDTOKEN_H
#include "token.hpp"

class CommandToken : public Token
{
    public:
    CommandToken(const std::string &token_value, int token_pos);
    virtual TokenType type() const override;
    virtual SubTokenType subType() const override;
    virtual std::vector<int> checkToken() const override;
    virtual void print() const override;
};

#endif
