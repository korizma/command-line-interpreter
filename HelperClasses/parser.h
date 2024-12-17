#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include "../CommandClasses/command.h"

class Parser 
{
    public:

        static Command* parse(const std::string& input);
    

    private:

        static Command* createCommand(const std::string& cmd_name, const std::vector<std::string>& arguments, const std::vector<std::string>& options);
        
        static std::vector<std::string> tokenize(const std::string& input, const bool& is_redirect = false);

        static std::vector<int> checkTokenSyntax(const std::string& token, const int& pos_in_line);

        static void checkTokensSemantics(std::vector<std::string>& args);

        static void tokenizeRedirect(std::vector<std::string>& args);

        static std::vector<int> checkTokenRedirectSyntax(const std::string& token, const int& pos_in_line);
};

#endif // PARSER_H