
#ifndef REDIRECTTOKEN_H
#define REDIRECTTOKEN_H
#include "token.h"


class RedirectToken : public Token
{
    private:
        bool _isInput;
        SubTokenType _subtype;
    public:
        // Constructor: sign and path as a single string
        RedirectToken(const std::string &sign_and_path, int token_pos)
            : Token(sign_and_path, token_pos)
        {
            int n = sign_and_path.length();
            int remove = 1;
            if (n > 1 && sign_and_path[0] == '>' && sign_and_path[1] == '>')
            {
                _isInput = false;
                _subtype = OutAppend;
                remove = 2;
            }
            else if (n > 0 && sign_and_path[0] == '>')
            {
                _isInput = false;
                _subtype = OutWrite;
            }
            else if (n > 0 && sign_and_path[0] == '<')
            {
                _isInput = true;
                _subtype = SubTokenNone;
            }
            if (n > 2)
            {
                setValue(sign_and_path.substr(remove, n - remove));
            }
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
