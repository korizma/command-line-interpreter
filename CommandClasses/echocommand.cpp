#include "echocommand.h"
#include <iostream>
#include <string>
#include "../ExceptionClasses/exception.h"

void EchoCommand::isValid() 
{
    if (arguments.size() > 1)
    {
        throw ArgumentException("this command takes only 1 argument!");
    }
    if (options.size() != 0)
    {
        throw OptionException("this command doesn't have options!");
    }
}


std::string EchoCommand::getType()
{
    return "echo";
}

void EchoCommand::execute()
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
        std::string cmd_input = io.getInput();
        arguments.push_back("\"" + cmd_input + "\"");
    }

    if (arguments[0][0] == '\"'|| arguments[0][0] == '\'')
        std::cout << arguments[0].substr(1, arguments[0].size()-2) << std::endl;
    else
    {
        try 
        {
            std::string file_input = io.readFile(arguments[0]);
            std::cout << file_input << std::endl;
        }
        catch (const FileException& e)
        {
            std::cerr << "File error: " << e.what() << std::endl;
        }
    }
}



