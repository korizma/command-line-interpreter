#include "rmcommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohelper.h"
#include <ctime>
#include <iomanip>

void RmCommand::isValid() 
{
    if (_args.size() != 1)
    {
        throw ArgumentException(1, _args.size());
    }
    if (_args.size() == 1 && _args[0]->subType() != ArgFile)
    {
        throw ArgumentException(true);
    }
    if (_options.size() != 0)
    {
        throw OptionException(0, _options.size());
    }
}

bool RmCommand::hasOutputStream() const
{
    return false;
}

std::string RmCommand::getType()
{
    return "rm";
}

std::string RmCommand::getOutput()
{  
    IOHelper io;
    io.deleteFile(_args[0]->value());
    return "";
}


