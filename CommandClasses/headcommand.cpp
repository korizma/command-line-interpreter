#include "headcommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohandler.h"

void HeadCommand::isValid() 
{
    if (arguments.size() > 1)
    {
        throw ArgumentException("this command takes only 1 argument!");
    }
    if (options.size() != 1)
    {        
        throw OptionException("this command takes only 1 option!");
    }
}


std::string HeadCommand::getType()
{
    return "head";
}

void HeadCommand::execute()
{
    try 
    {
        isValid();
    }    
    catch (const ArgumentException& e)
    {
        std::cerr << "Argument error: " << e.what() << std::endl;
        return;
    }
    catch (const OptionException& e)
    {
        std::cerr << "Option Error: " << e.what() << std::endl;
        return;
    }
    catch (const std::exception& e)
    {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return;
    }

    if (arguments.size() == 0)
    {
        std::string cmd_input = IOHandler::getInput();
        arguments.push_back("\"" + cmd_input + "\"");
    }

    std::string text;

    if (arguments[0][0] == '\"'|| arguments[0][0] == '\'')
        text = arguments[0].substr(1, arguments[0].size()-2);
    else
    {
        try 
        {
            text = IOHandler::readFile(arguments[0]);
        }
        catch (const FileException& e)
        {
            std::cerr << "File error: " << e.what() << std::endl;
        }
    }
    std::string lines = getNLines(text, )
}



