#include "trcommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohelper.h"

void TrCommand::isValid() 
{
    if (_args.size() != 2 && _args.size() != 3)
    {
        throw ArgumentException(3, _args.size());
    }
    if (_args.size() == 2 && _args[1]->subType() == ArgFile)
    {
        throw ArgumentException(false);
    }
    if (_args.size() == 3 && (_args[1]->subType() == ArgFile || _args[2]->subType() == ArgFile))
    {
        throw ArgumentException(false);
    }
    if (_options.size() != 0)
    {        
        throw OptionException(0, _options.size());
    }
}

bool TrCommand::needsInput() const
{
    return _args.size() == 1;
}

bool TrCommand::acceptsFileArgRead() const
{
    return true;
}

std::string TrCommand::getType()
{
    return "tr";
}

std::string TrCommand::getOutput()
{
    std::string text = _args[0]->value();

    std::string original = _args[1]->value();

    std::string replacement = _args[2]->value();

    int pos = 0;

    while ((pos = text.find(original, pos)) != std::string::npos) {
        text.replace(pos, original.length(), replacement);
        pos += replacement.length();
    }

    return text;
}


