#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include "../HelperClasses/iohelper.h"
#include <iostream>

class Command
{
    protected:
        std::vector<std::string> arguments;
        std::vector<std::string> options;

        std::string out;
        bool redirect_append;
        Command* next;

        IOHelper io;

        virtual void isValid() = 0;

        void output(std::string& text);

        virtual std::string getOutput() = 0;

        virtual void processInput();

    public:
        Command(const std::vector<std::string>& arguments, const std::vector<std::string>& options, Command* next_in_pipeline);
        ~Command();

        void execute();
        
        void acceptArgument(std::string& argument);

};

inline Command::Command( const std::vector<std::string>& arguments,
     const std::vector<std::string>& options, Command* next_in_pipeline) : options(options), next(next_in_pipeline)
        {
            redirect_append = false;
            for (int i = 0; i < arguments.size(); i++)
            {
                if (arguments[i][0] == '<' && arguments[i][1] == '<')
                {
                    out = arguments[i].substr(2, arguments[i].size()-2);
                    redirect_append = true;
                }
                else if (arguments[i][0] == '<')
                    out = arguments[i].substr(1, arguments[i].size()-1);
                else
                    this->arguments.push_back(arguments[i]);
            }
        }

inline Command::~Command()
{   
    if (next != NULL)
        delete next;
}

inline void Command::output(std::string& text)
{
    if (text == "" && next == NULL)
        return;
    
    if (out != "")
        if (redirect_append)
            io.appendFile(out, text);
        else
            io.writeFile(out, text);
    
    if (next == NULL)
        std::cout << text << std::endl;
    else
        next->acceptArgument(text);
}

inline void Command::acceptArgument(std::string& argument)
{
    if (arguments.size() == 0)
        arguments.push_back("\'" + argument + "\'");
    else
        arguments.insert(arguments.begin(), "\'" + argument + "\'");
}

inline void Command::execute()
{
    isValid();
    processInput();
    std::string text = getOutput();
    output(text);
    if (next)
        next->execute();
}

inline void Command::processInput()
{
    if (arguments.size() == 0)
    {
        std::string cmd_input = io.getInput();
        arguments.push_back("\"" + cmd_input + "\"");
    }
    if (arguments[0][0] != '\"' && arguments[0][0] != '\'')
    {
        std::string file_input = io.readFile(arguments[0]);
        arguments[0] = "\'" + file_input + "\'";
    }
}

#endif // COMMAND_H