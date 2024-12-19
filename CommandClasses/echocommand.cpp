#include "echocommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohandler.h"
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

void EchoCommand::execute()
{
    isValid();

    if (arguments.size() == 0)
    {
        std::string cmd_input = IOHandler::getInput();
        arguments.push_back("\"" + cmd_input + "\"");
    }

    if (arguments[0][0] == '\"'|| arguments[0][0] == '\'')
        std::cout << arguments[0].substr(1, arguments[0].size()-2) << std::endl;
    else
    {
        std::string file_input = IOHandler::readFile(arguments[0]);
        std::cout << file_input << std::endl;
    }
}



