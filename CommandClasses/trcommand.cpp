#include "trcommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohandler.h"

void TrCommand::isValid() 
{
    if (arguments.size() > 3 && arguments.size() < 2)
    {
        throw ArgumentException(2, arguments.size());
    }
    if (options.size() != 0)
    {        
        throw OptionException(0, options.size());
    }
}


std::string TrCommand::getType()
{
    return "tr";
}

std::string TrCommand::getOutput()
{
        return "";
}



