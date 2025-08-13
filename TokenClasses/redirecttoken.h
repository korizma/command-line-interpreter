
#ifndef REDIRECTTOKEN_H
#define REDIRECTTOKEN_H
#include "token.h"


class RedirectToken : public Token
{
    private:
        bool _isInput;
        SubTokenType _subtype;
    public:
        // Constructor: sign + path in one string
        RedirectToken(const std::string &token_value, int token_pos)
            : Token("", token_pos)
        {
            std::string path;
            if (token_value.size() >= 2 && token_value[0] == '>' && token_value[1] == '>')
            {
                _isInput = false;
                _subtype = OutAppend;
                path = token_value.substr(2);
            }
            else if (!token_value.empty() && token_value[0] == '>')
            {
                _isInput = false;
                _subtype = OutWrite;
                path = token_value.substr(1);
            }
            else if (!token_value.empty() && token_value[0] == '<')
            {
                _isInput = true;
                _subtype = SubTokenNone;
                path = token_value.substr(1);
            }
            else
            {
                _isInput = true;
                _subtype = SubTokenNone;
                path = token_value;
            }
            setValue(path);
        }

        // Constructor: sign and path as separate strings
        RedirectToken(const std::string &sign, const std::string &path, int token_pos)
            : Token(path, token_pos)
        {
            if (sign == ">>")
            {
                _isInput = false;
                _subtype = OutAppend;
            }
            else if (sign == ">")
            {
                _isInput = false;
                _subtype = OutWrite;
            }
            else if (sign == "<")
            {
                _isInput = true;
                _subtype = SubTokenNone;
            }
            else
            {
                _isInput = true;
                _subtype = SubTokenNone;
            }
        }

        virtual TokenType type() const override
        {
            return _isInput ? InRedirect : OutRedirect;
        }

        virtual SubTokenType subType() const override
        {
            return _subtype;
        }

        virtual std::vector<int> checkToken() const override
        {
            std::vector<int> errs;
            const std::string &val = value();
            int n = val.length();
            int start_pos = pos();
            for (int i = 0; i < n; ++i)
            {
                if (!std::isalnum(val[i]) && std::string(ARGALLOWEDCHRS).find(val[i]) == std::string::npos)
                {
                    errs.push_back(start_pos + i);
                }
            }
            return errs;
        }

        virtual void print() const override
        {
            Token::print();
            std::cout << "RedirectToken: ";
            if (_isInput)
            {
                std::cout << "Input";
            }
            else
            {
                if (_subtype == OutWrite)
                {
                    std::cout << "OutputWrite";
                }
                else if (_subtype == OutAppend)
                {
                    std::cout << "OutputAppend";
                }
                else
                {
                    std::cout << "Output";
                }
            }
            std::cout << std::endl;
        }
};

#endif
