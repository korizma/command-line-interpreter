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
        
        void acceptArgument(std::string& argument);

    public:
        Command(const std::vector<std::string>& arguments, const std::vector<std::string>& options, Command* next_in_pipeline);
        Command(const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string &output_redirect, bool is_append);
        ~Command();

        void execute();

        void setNext(Command *nextC);

        void print();

};

inline Command::Command(const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string &output_redirect, bool is_append)
         : arguments(arguments), options(options), out(output_redirect), redirect_append(is_append)
        { next = NULL;}

inline Command::~Command()
{   
    if (next != NULL)
        delete next;
}

inline void Command::output(std::string& text)
{
    if (text == "" && next == NULL)
        return;

    if (out.length() != 0)
    {
        if (redirect_append)
            io.appendFile(out, text);
        else
            io.writeFile(out, text);
        return;
    }
    
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

inline void Command::setNext(Command* nextC) { next = nextC;}

inline void Command::print()
{
    std::cout << "Command: ";
    for (const auto& arg : arguments)
        std::cout << "[" << arg << "] ";
    std::cout << "\nOptions: ";
    for (const auto& opt : options)
        std::cout << "[" << opt << "] ";
    std::cout << "\nOutput redirect: [" << out << "] len: " << out.length();
    std::cout << "\nRedirect append: " << (redirect_append ? "true" : "false") << std::endl;
    if (next != NULL)
    {
        std::cout << "Next command: " << std::endl;
        next->print();
    }
    else
        std::cout << "No next command." << std::endl;
}

#endif // COMMAND_H