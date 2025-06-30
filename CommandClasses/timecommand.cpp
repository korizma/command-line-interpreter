#include "timecommand.h"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

void TimeCommand::isValid() 
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


std::string TimeCommand::getType()
{
    return "time";
}

void TimeCommand::execute()
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

    std::time_t current_time = std::time(nullptr);
    std::tm* local_time = std::localtime(&current_time);
    std::cout << std::put_time(local_time, "%H:%M:%S") << std::endl;
}



