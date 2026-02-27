#include "echocommand.hpp"
#include <iostream>
#include <string>
#include "../HelperClasses/iohelper.hpp"
#include "../ExceptionClasses/exception.hpp"

bool EchoCommand::needsInput() const
{
    return _args.empty();
}

bool EchoCommand::acceptsFileArgRead() const
{
    return true;
}

void EchoCommand::isValid() 
{
    if (_args.size() != 1)
    {
        throw ArgumentException(1, _args.size());
    }
    if (_options.size() != 0)
    {
        throw OptionException(0, _options.size());
    }
}


std::string EchoCommand::getType()
{
    return "echo";
}

std::string EchoCommand::getOutput()
{
    return _args[0]->value();
}


