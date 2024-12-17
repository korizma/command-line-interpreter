#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <cctype>
#include <vector>
#include <fstream>

class Command
{
    protected:
        std::vector<std::string> arguments;
        std::vector<std::string> options;

        std::string out;

        virtual void isValid() = 0;


    public:
        Command(const std::vector<std::string>& arguments, const std::vector<std::string>& options);
        ~Command();

        virtual void execute() = 0;

};

inline Command::Command( const std::vector<std::string>& arguments,
     const std::vector<std::string>& options) : options(options)
        {
            for (int i = 0; i < arguments.size(); i++)
            {
                if (arguments[i][0] == '<')
                    out = arguments[i];
                else
                    this->arguments.push_back(arguments[i]);
            }
        }

inline Command::~Command()
{}



#endif // COMMAND_H