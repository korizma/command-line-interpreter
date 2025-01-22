#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include "../HelperClasses/iohandler.h"

class Command
{
    protected:
        std::vector<std::string> arguments;
        std::vector<std::string> options;

        std::string out;
        Command* next;

        virtual void isValid() = 0;

        void output(std::string& text);

        virtual std::string getOutput() = 0;

    public:
        Command(const std::vector<std::string>& arguments, const std::vector<std::string>& options, Command* next_in_pipeline);
        ~Command();

        void execute();
        
        void acceptArgument(std::string& argument);

};

inline Command::Command( const std::vector<std::string>& arguments,
     const std::vector<std::string>& options, Command* next_in_pipeline) : options(options), next(next_in_pipeline)
        {
            for (int i = 0; i < arguments.size(); i++)
            {
                if (arguments[i][0] == '<')
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
        if (out[0] == '<')
            IOHandler::appendFile(out.substr(1, out.size()-1), text);
        else
            IOHandler::writeFile(out, text);
    
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
    std::string text = getOutput();
    output(text);
    if (next)
        next->execute();
}



#endif // COMMAND_H