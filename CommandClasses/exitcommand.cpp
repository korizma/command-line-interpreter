#include "exitcommand.h"
#include <iostream>
#include <string>

void ExitCommand::isValid() 
{
    if (_args.size() != 0)
    {
        throw ArgumentException(0, _args.size());
    }
    if (_options.size() != 0)
    {
        throw OptionException(0, _options.size());
    }
}

bool ExitCommand::hasOutputStream() const
{
    return false;
}

std::string ExitCommand::getType()
{
    return "exit";
}

std::string ExitCommand::getOutput()
{
    exit(0);
    return "";
}



