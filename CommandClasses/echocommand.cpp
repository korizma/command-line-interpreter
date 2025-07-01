#include "echocommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohelper.h"
#include "../ExceptionClasses/exception.h"

void EchoCommand::isValid() 
{
    if (arguments.size() > 1)
    {
        throw ArgumentException(1, arguments.size());
    }
    if (options.size() != 0)
    {
        throw OptionException(0, options.size());
    }
}


std::string EchoCommand::getType()
{
    return "echo";
}

std::string EchoCommand::getOutput()
{
    if (arguments.size() == 0)
    {
        std::string cmd_input = io.getInput();
        arguments.push_back("\"" + cmd_input + "\"");
    }

    if (arguments[0][0] == '\"'|| arguments[0][0] == '\'')
        return arguments[0].substr(1, arguments[0].size()-2);
    else
    {
        std::string file_input = io.readFile(arguments[0]);
        return file_input;
    }
}



