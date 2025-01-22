#include "wccommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohandler.h"
#include <ctime>
#include <iomanip>

void WcCommand::isValid() 
{
    if (arguments.size() > 1)
    {
        throw ArgumentException(1, arguments.size());
    }
    if (options.size() == 1 && options[0] != "-w" && options[0] != "-c")
    {
        throw OptionException(options[0]);
    }
    if (options.size() != 1)
    {
        throw OptionException(1, options.size());
    }
}


std::string WcCommand::getType()
{
    return "wc";
}

std::string WcCommand::getOutput()
{
        if (arguments.size() == 0)
    {
        std::string cmd_input = IOHandler::getInput();
        arguments.push_back("\"" + cmd_input + "\"");
    }

    
    if (arguments[0][0] != '\'' && arguments[0][0] != '\"')
    {
        std::string file_input = IOHandler::readFile(arguments[0]);
        arguments[0] = file_input;
    } 
    else
    {
        arguments[0] = arguments[0].substr(1, arguments[0].size()-2);
    }

    if (options[0] == "-c")
    {
        return std::to_string(arguments[0].size());
    }
    if (options[0] == "-w")
    {
        int i = 0, counter = 0;
        char last = 'a';
        arguments[0] += " ";
        while (i < arguments[0].size())
        {
            if (!std::isspace(last) && std::isspace(arguments[0][i]))
                counter++;
            last = arguments[0][i];
            i++;
        }
        return std::to_string(counter);
    }
    return "";
}



