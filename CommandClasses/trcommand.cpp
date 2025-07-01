#include "trcommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohelper.h"

void TrCommand::isValid() 
{
    if (arguments.size() != 3)
    {
        throw ArgumentException(2, arguments.size());
    }
    if (options.size() != 0)
    {        
        throw OptionException(0, options.size());
    }
}


std::string TrCommand::getType()
{
    return "tr";
}

std::string TrCommand::getOutput()
{
    std::string text;
    if (arguments[0][0] == '\"'|| arguments[0][0] == '\'')
        text = arguments[0].substr(1, arguments[0].size()-2);
    else
    {
        std::string file_input = io.readFile(arguments[0]);
        text = file_input;
    }
    std::string original;
    if (arguments[1][0] == '\"' || arguments[1][0] == '\'')
        original = arguments[1].substr(1, arguments[1].size() - 2);
    else
        throw ArgumentException(1, arguments[1].size());

    std::string replacement;
    if (arguments[2][0] == '\"' || arguments[2][0] == '\'')
        replacement = arguments[2].substr(1, arguments[2].size() - 2);
    else
        throw ArgumentException(2, arguments[2].size());

    int pos = 0;

    while ((pos = text.find(original, pos)) != std::string::npos) {
        text.replace(pos, original.length(), replacement);
        pos += replacement.length();
    }

    return text;
}



