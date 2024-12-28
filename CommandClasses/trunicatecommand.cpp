#include "trunicatecommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohandler.h"
#include <ctime>
#include <iomanip>

void TrunicateCommand::isValid() 
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


std::string TrunicateCommand::getType()
{
    return "trunicate";
}

std::string TrunicateCommand::getOutput()
{
        
    IOHandler::clearFile(arguments[0]);
    
    return "";
}



