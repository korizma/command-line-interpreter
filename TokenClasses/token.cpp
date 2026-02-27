#include "token.hpp"
#include "argumenttoken.hpp"
#include "redirecttoken.hpp"
#include "optiontoken.hpp"
#include "commandtoken.hpp"

Token* Token::createToken(const std::string &token_value, int token_pos, const std::string &next_value, int next_pos)
{
    // "<" "input.txt" case
    if ((token_value == "<" || token_value == ">>" || token_value == ">") && next_pos != -1)
        return new RedirectToken(token_value, next_value, next_pos);

    // "<input.txt" case
    if (token_value.size() > 1 && (token_value[0] == '>' || token_value[0] == '<'))
    {
        return new RedirectToken(token_value, token_pos);
    }

    // "|" "command" case
    if (token_value == "|" && next_pos != -1)
        return new CommandToken(next_value, next_pos);

    // option case
    if (token_value[0] == '-' && next_pos == -1)
        return new OptionToken(token_value, token_pos);

    // argument case
    return new ArgumentToken(token_value, token_pos);
}