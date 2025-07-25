#include "rmcommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohelper.h"
#include <ctime>
#include <iomanip>

void RmCommand::isValid() 
{
    if (arguments.size() != 1)
    {
        throw ArgumentException(1, arguments.size());
    }
    if (arguments.size() == 1 && (arguments[0][0] == '\'' || arguments[0][0] == '\"'))
    {
        throw ArgumentException(true);
    }
    if (options.size() != 0)
    {
        throw OptionException(0, options.size());
    }
}

std::string RmCommand::getType()
{
    return "rm";
}

std::string RmCommand::getOutput()
{  
    io.deleteFile(arguments[0]);

    return "";
}


void RmCommand::processInput() {}

