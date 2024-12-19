#include "headcommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohandler.h"

void HeadCommand::isValid() 
{
    if (arguments.size() > 1)
    {
        throw ArgumentException(1, arguments.size());
    }
    if (options.size() == 1 && options[0] != "-n")
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

void HeadCommand::execute()
{
    isValid();

    
}



