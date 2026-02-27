
#ifndef REDIRECTTOKEN_H
#define REDIRECTTOKEN_H
#include "token.hpp"


class RedirectToken : public Token
{
    private:
        bool _isInput;
        SubTokenType _subtype;
    public:
    RedirectToken(const std::string &sign_and_path, int token_pos);
    RedirectToken(const std::string &sign, const std::string &path, int token_pos);
    virtual TokenType type() const override;
    virtual SubTokenType subType() const override;
    virtual std::vector<int> checkToken() const override;
    virtual void print() const override;
};

#endif
