#include "exitcommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohandler.h"

void ExitCommand::isValid() 
{
    if (arguments.size() != 0)
    {
        throw ArgumentException(0, arguments.size());
    }
    if (options.size() != 0)
    {
        
        throw OptionException(0, options.size());
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



