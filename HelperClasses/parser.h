#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "../CommandClasses/command.h"

class Parser 
{
    public:

        static Command* parse(std::string input);
    

    private:

        static Command* createCommand(const std::string& cmd_name, std::string original_command, const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string& in, const std::string& out);
        
};

#endif // PARSER_H