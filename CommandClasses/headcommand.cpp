#include "headcommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohelper.h"

bool HeadCommand::needsInput() const
{
    return _args.empty();
}

bool HeadCommand::acceptsFileArgRead() const
{
    return true;
}

void HeadCommand::isValid() 
{
    if (_args.size() != 1)
    {
        throw ArgumentException(1, _args.size());
    }
    if (_options.size() == 1 && (_options[0]->value()[1] != 'n' || _options[0]->value().size() > 7 || _options[0]->value().size() < 3))
    {
        throw OptionException(_options[0]->value());
    }
    if (_options.size() != 1)
    {
        throw OptionException(1, _options.size());
    }
}


std::string HeadCommand::getType()
{
    return "head";
}

std::string HeadCommand::getOutput()
{
    int x = std::stoi(_options[0]->value().substr(2, _options[0]->value().size()-2));

    int i;
    for (i = 0; i < _args[0]->value().size(); i++)
    {
        if (x == 0)
            break;
        if (_args[0]->value()[i] == '\n')
            x--;
    }

    return _args[0]->value().substr(0, i);
}



