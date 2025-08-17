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
        IOHelper _io;

        bool _is_pipeline_cmd;

        InputStream* _input_redirect;
        OutStream* _output_redirect;

        std::string _original_line;
        std::vector<Token*> _cmd_tokens;

        Token* _command_token;
        std::vector<Token*> _args, _options;

        Command* _final_command;

        // creates the command based on the parsers data
        virtual void createCommand();

        // classifies the tokens in their respective roles
        void classifyTokens();

        Parser();

    private:

        // tokenizes the input line 
        void seperateOnWhitespaces();

        // called in the seperateOneWhitespaces function to finish the tokenizing
        void tokenize(std::vector<std::string> &tokens, std::vector<int> &token_indx);

        // if the original line is a pipeline command this function parses it
        Command* createPipeline();

};

#endif // PARSER_H