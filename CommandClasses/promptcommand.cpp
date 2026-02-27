#include "promptcommand.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "../terminal.hpp"
#include "../ExceptionClasses/exception.hpp"

void PromptCommand::isValid() 
{
    if (_args.size() != 1)
    {
        throw ArgumentException(1, _args.size());
    }
    if (_args.size() == 1 && _args[0]->subType() == ArgString)
    {
        throw ArgumentException(false);
    }
    if (_options.size() != 0)
    {
        throw OptionException(0, _options.size());
    }
}

bool PromptCommand::hasOutputStream() const
{
    return false;
}

std::string PromptCommand::getType()
{
    return "prompt";
}

std::string PromptCommand::getOutput()
{

    Terminal::getInstance()->changeSign(_args[0]->value());

    return "";
}

