#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <vector>
#include <fstream>
#include "../HelperClasses/iohelper.h"

class Command
{
    protected:
        std::string original_command;

        std::vector<std::string> arguments;
        std::vector<std::string> options;

        std::string in;
        std::string out;

        IOHelper io;

        virtual void isValid() = 0;


    public:
        Command(std::string original_command, const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string& in, const std::string& out);
        ~Command();

        virtual void execute() = 0;

};

inline Command::Command(std::string original_command, const std::vector<std::string>& arguments,
     const std::vector<std::string>& options,
     const std::string& in, const std::string& out)
        :

        original_command(original_command), arguments(arguments), options(options), in(in), out(out) {}

inline Command::~Command()
{}



#endif // COMMAND_H