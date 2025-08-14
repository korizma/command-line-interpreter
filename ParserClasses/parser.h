#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include "../CommandClasses/command.h"
#include "../HelperClasses/iohelper.h"
#include "../config.h"
#include "../TokenClasses/token.h"

class Parser 
{
    public:

        Command* parse();

        Parser(std::string &line);

        void print();

    private:
        IOHelper _io;

        bool _is_pipeline_cmd;

        Token* _input_redirect, *_output_redirect;

        std::string _original_line;
        std::vector<Token*> _cmd_tokens;

        Token* _command_token;
        std::vector<Token*> _args, _options;

        Command* _final_command;

        // tokenizes the input line 
        void seperateOnWhitespaces();

        // called in the seperateOneWhitespaces function to finish the tokenizing
        void tokenize(std::vector<std::string> &tokens, std::vector<int> &token_indx);

        // reads the input redirect into the original line
        void readRedirect();

        // checks if the tokens read from the input redirect are all args
        void checkRedirectTokens();

        // classifies the tokens in their respective roles
        void classifyTokens();

        // checks for semantic errors in the tokens (invalid order of args)
        void semanticTokenAnalysis();

        // checks for syntax errors in the tokens (unwanted chars, invalid formats)
        void syntaxTokenAnalysis();

        // checks for semantic errors in the tokens (flow collisions)
        void semanticFlowAnalysis();

        // creates the command based on the parsers data
        void createCommand();

        // command creator for parts of the pipeline, only called in the createPipeline function
        Command* parsePipelineCmd();

        // if the original line is a pipeline command this function parses it
        Command* createPipeline();
        
        // constructor for the command pipeline part
        Parser(const std::string cmd_name, std::vector<Token*> &tokens, bool first_command, std::string in_redirect, std::string out_redirect, bool out_append);

};

#endif // PARSER_H