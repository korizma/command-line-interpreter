#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include "../CommandClasses/command.h"
#include "iohelper.h"
#include "config.h"

class Parser 
{
    public:

        Command* parse();

        Parser(std::string &line);
    

    private:
        IOHelper io;

        bool is_pipeline_cmd;
        bool has_regular_args;

        std::string input_redirect, output_redirect;

        std::string original_line;
        std::vector<std::string> tokens;
        
        std::string command_name;
        std::vector<std::string> args, options;

        Command* final_command;

        void seperateOnWhitespaces();

        void tokenize();

        void readRedirect();

        Command* parsePipelineCmd();

        void classifyTokens();

        Command* createCommand();

        TokenType classifyToken();

};

#endif // PARSER_H