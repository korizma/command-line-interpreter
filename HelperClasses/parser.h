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
        void print();

    

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

        bool is_first_in_pipeline;

        void seperateOnWhitespaces();

        void tokenize(std::vector<std::string> &tokens, std::vector<int> &token_indx);

        void readRedirect();

        void classifyTokens();

        void semanticTokenAnalysis();

        void syntaxTokenAnalysis();

        void semanticFlowAnalysis();

        void createCommand();

        Command* parsePipelineCmd();
        
        Command* createPipeline();

        Parser(const std::string cmd_name, std::vector<Token*> &tokens, bool first_command, std::string in_redirect, std::string out_redirect, bool out_append);

};

#endif // PARSER_H