#include "trunicatecommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohandler.h"
#include <ctime>
#include <iomanip>

void TrunicateCommand::isValid() 
{
    if (arguments.size() != 1)
    {
        throw ArgumentException(1, arguments.size());
    }
    if (arguments.size() == 1 && (arguments[0][0] == '\'' || arguments[0][0] == '\"'))
    {
        throw ArgumentException(true);
    }
    if (options.size() != 0)
    {
        throw OptionException(0, options.size());
    }
}


std::string TrunicateCommand::getType()
{
    return "trunicate";
}

void TrunicateCommand::execute()
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
        IOHandler::clearFile(arguments[0]);
    }
    catch (const FileException& e)
    {
        std::cerr << "File error: " << e.what() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
}



