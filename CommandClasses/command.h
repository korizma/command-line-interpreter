#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <cctype>
#include <vector>
#include <iostream>
#include "../StreamClasses/InStream/inputstream.h"
#include "../StreamClasses/InStream/stdinstream.h"
#include "../StreamClasses/OutStream/outstream.h"

class Command
{
    private:
        InputStream* _input_stream;
        OutStream* _output_stream;

        Command* _next_command;
        bool _is_pipeline_cmd;

    protected:
        Command(InputStream* inputStream, OutStream* outputStream, std::vector<Token*> options);

        std::vector<Token*> _args;
        std::vector<Token*> _options;

        // checks for validity of args and options
        virtual void isValid() = 0;

        // command logic in here
        virtual std::string getOutput() = 0;

        // this needs to be overridden if the command accepts input
        virtual bool needsInput() const;

        // for pipeline error handling
        // this needs to be overridden if the command has output
        virtual bool acceptsFileArgRead() const;

        void setInputStream(InputStream* input_stream);

    public:
        
        ~Command();

        void execute();

        void print();

        virtual bool hasOutputStream() const;

        // sets the next command to be executed
        void setNextCommand(Command* next);
};

#endif // COMMAND_H