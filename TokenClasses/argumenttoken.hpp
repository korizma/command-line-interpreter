#ifndef ARGUMENTTOKEN_H
#define ARGUMENTTOKEN_H
#include "token.hpp"

class ArgumentToken : public Token 
{
    private:
        SubTokenType _subtype;
        bool _is_valid_string;

    public:
        ArgumentToken(const std::string& token_value, int token_pos);

        virtual TokenType type() const override;

    virtual SubTokenType subType() const override;
    virtual std::vector<int> checkToken() const override;
    virtual void print() const override;
};

#endif
