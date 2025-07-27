#ifndef TOKENCHECKER_H
#define TOKENCHECKER_H
#include <string>
#include <vector>
#include <algorithm>
#include "../config.h"

class Token;

class TokenChecker
{
    private:

        std::vector<int> checkArgument(const std::string &token);

        std::vector<int> checkOption(const std::string &token);

        std::vector<int> checkRedirect(const std::string &token, bool has_extra);

    public:
        TokenChecker();

        std::vector<int> check(Token *token);
};



#endif