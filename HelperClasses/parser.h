#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include "../CommandClasses/command.h"
#include "iohelper.h"
#include "../config.h"
#include "token.h"

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
        bool output_redirect_append;

        std::string original_line;
        std::vector<Token*> cmd_tokens;
        
        std::string command_name;
        std::vector<std::string> args, options;

        Command* final_command;

        void seperateOnWhitespaces();

        void tokenize(std::vector<std::string> &tokens, std::vector<int> &token_indx);

        void readRedirect();

        Command* parsePipelineCmd();

        void classifyTokens();

        void semanticTokenAnalysis();

        void syntaxTokenAnalysis();

        void semanticFlowAnalysis();

        Command* createCommand();

        void print();

};

#endif // PARSER_H