#include "promptcommand.h"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "../terminal.h"
#include "../ExceptionClasses/exception.h"

void PromptCommand::isValid() 
{
    if (arguments.size() != 1)
    {
        throw ArgumentException(1, arguments.size());
    }
    if (arguments.size() == 1 && !(arguments[0][0] == '\'' || arguments[0][0] == '\"'))
    {
        throw ArgumentException(false);
    }
    if (options.size() != 0)
    {
        throw OptionException(0, options.size());
    }
}


std::string PromptCommand::getType()
{
    return "prompt";
}

std::string PromptCommand::getOutput()
{
        
    Terminal::getInstance()->changeSign(arguments[0].substr(1, arguments[0].size()-2));

    return "";
}


void PromptCommand::processInput() {}


