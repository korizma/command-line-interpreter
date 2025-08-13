#include "wccommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohelper.h"
#include <ctime>
#include <iomanip>

void WcCommand::isValid() 
{
    if (_args.size() != 1)
    {
        throw ArgumentException(1, _args.size());
    }
    if (_options.size() == 1 && _options[0]->value() != "-w" && _options[0]->value() != "-c")
    {
        throw OptionException(_options[0]->value());
    }
    if (_options.size() != 1)
    {
        throw OptionException(1, _options.size());
    }
}

bool WcCommand::needsInput() const
{
    return _args.empty();
}

bool WcCommand::acceptsFileArgRead() const
{
    return true;
}

std::string WcCommand::getType()
{
    return "wc";
}

std::string WcCommand::getOutput()
{
    if (_options[0]->value() == "-c")
    {
        return std::to_string(_args[0]->value().size());
    }
    if (_options[0]->value() == "-w")
    {
        int i = 0, counter = 0;
        char last = 'a';
        _args[0]->value() += " ";
        while (i < _args[0]->value().size())
        {
            if (!std::isspace(last) && std::isspace(_args[0]->value()[i]))
                counter++;
            last = _args[0]->value()[i];
            i++;
        }
        return std::to_string(counter);
    }
    return "";
}



