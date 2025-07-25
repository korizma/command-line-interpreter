#include "headcommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohelper.h"

void HeadCommand::isValid() 
{
    if (arguments.size() > 1)
    {
        throw ArgumentException(1, arguments.size());
    }
    if (options.size() == 1 && (options[1] != "n" || options[0].size() > 7))
    {
        throw OptionException(options[0]);
    }
    if (options.size() != 1)
    {        
        throw OptionException(1, options.size());
    }
}


std::string HeadCommand::getType()
{
    return "head";
}

std::string HeadCommand::getOutput()
{
    int x = std::stoi(options[0].substr(2, options[0].size()-2));

    int i;
    for (i = 0; i < arguments[0].size(); i++)
    {
        if (x == 0)
            break;
        if (arguments[0][i] == '\n')
            x--;
    }
    
    return arguments[0].substr(0, i);
}



