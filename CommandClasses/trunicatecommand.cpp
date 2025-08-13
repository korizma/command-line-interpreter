#include "trunicatecommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohelper.h"
#include <ctime>
#include <iomanip>

void TrunicateCommand::isValid() 
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

bool TrunicateCommand::hasOutputStream() const
{
    return false;
}

std::string TrunicateCommand::getType()
{
    return "trunicate";
}

std::string TrunicateCommand::getOutput()
{   
    IOHelper io;
    io.clearFile(_args[0]->value());
    return "";
}



