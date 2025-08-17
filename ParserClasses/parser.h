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

        virtual Command* parse();

        Parser(std::string &line);

        void print();

    protected:

        // parse the command that is in the pipeline
        Command* parsePipelineCommand();


        // constructor for the command pipeline part
        Parser(std::vector<Token*> tokens, InputStream* in_stream, OutStream* out_stream);

        IOHelper _io;

        bool _is_pipeline_cmd;

        InputStream* _input_redirect;
        OutStream* _output_redirect;

        std::string _original_line;
        std::vector<Token*> _cmd_tokens;

        Token* _command_token;
        std::vector<Token*> _args, _options;

        // creates the command based on the parsers data
        virtual void createCommand();

    private:

        Command* _final_command;

        // tokenizes the input line 
        void seperateOnWhitespaces();

        // called in the seperateOneWhitespaces function to finish the tokenizing
        void tokenize(std::vector<std::string> &tokens, std::vector<int> &token_indx);

        // classifies the tokens in their respective roles
        void classifyTokens();

        // if the original line is a pipeline command this function parses it
        Command* createPipeline();
        
};

#endif // PARSER_H