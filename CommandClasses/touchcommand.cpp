#include "touchcommand.h"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

void TouchCommand::isValid() 
{
    if (arguments.size() != 1)
    {
        throw ArgumentException("this command takes only 1 argument!");
    }
    if (arguments.size() == 1 && (arguments[0][0] == '\'' || arguments[0][0] == '\"'))
    {
        throw ArgumentException("argument format invalid!");
    }
    if (options.size() != 0)
    {
        throw OptionException("this command doesn't have options!");
    }
}


std::string TouchCommand::getType()
{
    return "touch";
}

void TouchCommand::execute()
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
    try
    {
        io.createFile(arguments[0]);   
    }
    catch(const FileException e)
    {
        std::cerr << "File error: " << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return;
    }
}



