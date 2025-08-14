#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <vector>
#include "../config.h"
#include <iostream>


class Token
{
    private:
        std::string _value;
        int _pos;

    protected:
        void setValue(const std::string &value);

    public:
    Token(std::string token_value, int token_pos) : _value(token_value), _pos(token_pos) {}

    virtual TokenType type() const = 0;

    virtual SubTokenType subType() const = 0;

    virtual std::string value() const;

    virtual int pos() const;

    virtual std::vector<int> checkToken() const = 0;

    virtual void print() const;

    static Token* createToken(const std::string &token_value, int token_pos, const std::string &next_value = "", int next_pos = -1);

};

inline void Token::setValue(const std::string &value)
{
    _value = value;
}

inline std::string Token::value() const
{
    return _value;
}

inline int Token::pos() const
{
    return _pos;
}

inline void Token::print() const
{
    std::cout << "Token: " << _value << ", Position: " << _pos << std::endl;
}

#endif