#include "exitcommand.h"
#include <iostream>
#include <string>

void ExitCommand::isValid() 
{
    if (arguments.size() != 0)
    {
        throw ArgumentException("this command doesn't take arguments!");
    }
    if (options.size() != 0)
    {
        throw OptionException("this command doesn't have options!");
    }
}


std::string ExitCommand::getType()
{
    return "exit";
}

void ExitCommand::execute()
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
    
    exit(0);
}



