#include "argumenttoken.hpp"

ArgumentToken::ArgumentToken(const std::string& token_value, int token_pos)
            : Token(token_value, token_pos)
        {
            _is_valid_string = (token_value[0] == token_value[token_value.length() - 1]) && (token_value[0] == '"' || token_value[0] == '\'');
            if (!token_value.empty() && (token_value[0] == '"' || token_value[0] == '\''))
            {
                if (token_value.length() >= 2)
                    setValue(token_value.substr(1, token_value.length() - 2));
                _subtype = ArgString;
            }
            else
                _subtype = ArgFile;
        }


TokenType ArgumentToken::type() const
{
    return Argument;
}

SubTokenType ArgumentToken::subType() const
{
    return _subtype;
}

std::vector<int> ArgumentToken::checkToken() const
{
    std::vector<int> errs;
    const std::string& val = value();
    int n = val.length();
    if (_subtype == ArgString)
    {
        if (n < 2 || !_is_valid_string)
        {
            errs.push_back(pos()); // sets the error at the starting position of the token
        }
    }
    else if (_subtype == ArgFile)
    {
        for (int i = 0; i < n; ++i)
        {
            if (!std::isalnum(val[i]) && std::string(ARGALLOWEDCHRS).find(val[i]) == std::string::npos)
            {
                errs.push_back(i + pos());
            }
        }
    }
    return errs;
}

void ArgumentToken::print() const
{
    Token::print();
    std::cout << "SubType: " << (_subtype == ArgString ? "String" : "File") << std::endl;
}