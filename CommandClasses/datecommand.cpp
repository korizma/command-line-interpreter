#include "datecommand.h"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "../ExceptionClasses/exception.h"

void DateCommand::isValid() 
{
    if (_args.size() != 0)
    {
        throw ArgumentException(0, _args.size());
    }
    if (_options.size() != 0)
    {
        throw OptionException(0, _options.size());
    }
}

std::string DateCommand::getType()
{
    return "date";
}

std::string DateCommand::getOutput()
{
    std::time_t current_time = std::time(nullptr);
    std::tm* local_time = std::localtime(&current_time);
    std::ostringstream oss;
    oss << std::put_time(local_time, "%Y-%m-%d");
    return oss.str();
}

