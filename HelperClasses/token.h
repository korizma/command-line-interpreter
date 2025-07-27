#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <vector>
#include <algorithm>
#include "../config.h"
#include "tokenchecker.h"
#include <iostream>

class Token
{
    private:
        TokenType type_;
        std::string value_;
        int start_indx_in_line;

        std::string extra_value_;
        int extra_start_indx_in_line;

    public:
        Token(const std::string &value, int start_indx_in_line, const std::string &extra_value = "", int extra_start_indx_in_line = -1);

        std::vector<int> check();

        TokenType type() const;

        int indx() const;

        std::string value() const;

        bool has_extra() const;

        void print();

        bool isAppendOutputRedirect() const;
};

inline Token::Token(const std::string &value, int start_indx_in_line, const std::string &extra_value, int extra_start_indx_in_line)
: value_(value), extra_value_(extra_value), start_indx_in_line(start_indx_in_line), extra_start_indx_in_line(extra_start_indx_in_line)
{
    if (extra_value != "")
    {
        if (value_ == "<")
            type_ = InRedirect;
        else
            type_ = OutRedirect;
    }
    else
    {
        switch (value[0])
        {
            case '-':
                type_ = Option;
                break;
            case '|':
                type_ = PipeSign;
                break;
            case '<':
                type_ = InRedirect;
                break;
            case '>':
                type_ = OutRedirect;
                break;
            default:
                type_ = Arg;
        }
    }
}

inline TokenType Token::type() const {return type_;}

inline int Token::indx() const 
{ 
    if (extra_value_ == "")
        return start_indx_in_line;
    return extra_start_indx_in_line;
}

inline std::string Token::value() const 
{
    if (extra_value_ == "")
            return value_;
    return extra_value_;
}

inline std::vector<int> Token::check()
{
    TokenChecker tk = TokenChecker();
    return tk.check(this);
}

inline bool Token::has_extra() const
{
    return extra_value_ != "";
}

inline bool Token::isAppendOutputRedirect() const
{
    return type_ == OutRedirect && value_ == ">>";
}

inline void Token::print()
{
    std::cout << "Token: " << value() << " at position: " << indx() << std::endl;
}

#endif