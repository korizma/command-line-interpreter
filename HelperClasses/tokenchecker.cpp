#include "tokenchecker.h"
#include "token.h"

TokenChecker::TokenChecker() {}

std::vector<int> TokenChecker::checkArgument(const std::string &token)
{
    int n = token.length();
    std::vector<int> errs;
    if (token[0] == token[n - 1] && (token[0] == '\'' || token[0] == '\"'))
        return errs;

    for (int i = 0; i < n; i++)
    {
        if (!std::isalnum(token[i]) && token[i] != '\\' && token[i] != '.' && token[i] != '_')
            errs.push_back(i);
    }
    return errs;
}

 std::vector<int> TokenChecker::checkOption(const std::string &token)
{
    int n = token.length();
    std::vector<int> errs;

    for (int i = 1; i < n; i++)
    {
        if (!std::isalnum(token[i]))
            errs.push_back(i);
    }
    return errs;
}

 std::vector<int> TokenChecker::checkRedirect(const std::string &token, bool has_extra)
{
    int n = token.length();
    int start = 0;
    if (!has_extra)
    {
        if (token[0] == '<')
            start = 1;
        else if (token[0] == '>' && token[1] == '>')
            start = 2;
        else if (token[0] == '>')
            start = 1;

    }
    std::vector<int> errs;

    for (int i = start; i < n; i++)
    {
        if (token[i] != '.' && !std::isalnum(token[i]))
            errs.push_back(i);
    }

    return errs;
}

 std::vector<int> TokenChecker::check(Token *token)
{
    if (token == NULL)
        return {};

    std::vector<int> errs;
    switch (token->type())
    {
        case Arg:
            errs = checkArgument(token->value());
            break;
        case Option:
            errs = checkOption(token->value());
            break;
        case InRedirect:
            errs = checkRedirect(token->value(), token->has_extra());
            break;
        case OutRedirect:
            errs = checkRedirect(token->value(), token->has_extra());
            break;
        case PipeSign:
            return {};
    }

    for (int i = 0; i < errs.size(); i++)
    {
        errs[i] += token->indx();
    }

    return errs;
}