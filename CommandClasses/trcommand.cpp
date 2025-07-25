#include "trcommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohelper.h"

void TrCommand::isValid() 
{
    if (arguments.size() < 1 && arguments.size() > 3)
    {
        throw ArgumentException(3, arguments.size());
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
    std::string text = arguments[0].substr(1, arguments[0].size()-2);

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

void TrCommand::processInput()
{
    if (arguments.size() == 1)
    {
        std::string cmd_input = io.getInput();
        arguments.insert(arguments.begin(), "\"" + cmd_input + "\"");
    }
    if (arguments[0][0] != '\"' && arguments[0][0] != '\'')
    {
        std::string file_input = io.readFile(arguments[0]);
        arguments[0] = "\'" + file_input + "\'";
    }
}

