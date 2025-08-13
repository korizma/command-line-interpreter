#include "touchcommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohelper.h"
#include <ctime>
#include <iomanip>

void TouchCommand::isValid() 
{
    if (_args.size() != 1)
    {
        throw ArgumentException(1, _args.size());
    }
    if (_args.size() == 1 && _args[0]->subType() == ArgString)
    {
        throw ArgumentException(true);
    }
    if (_options.size() != 0)
    {
        throw OptionException(0, _options.size());
    }
}


std::string TouchCommand::getType()
{
    return "touch";
}

std::string TouchCommand::getOutput()
{
    IOHelper io;
    io.createFile(_args[0]->value());  

    return ""; 
}


