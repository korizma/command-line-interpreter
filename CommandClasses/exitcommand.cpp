#include "exitcommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohandler.h"

void ExitCommand::isValid() 
{
    if (arguments.size() != 0)
    {
        throw ArgumentException(0, arguments.size());
    }
    if (options.size() != 0)
    {
        
        throw OptionException(0, options.size());
    }
}


std::string ExitCommand::getType()
{
    return "exit";
}

void ExitCommand::execute()
{
    isValid();
    
    exit(0);
}



