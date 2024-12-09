#include "wccommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohandler.h"
#include <ctime>
#include <iomanip>

void WcCommand::isValid() 
{
    if (arguments.size() > 1)
    {
        throw ArgumentException("this command takes only 1 argument!");
    }
    if (options.size() != 1)
    {
        if (options[0] != "-w" && options[0] != "-c")
        {
            throw OptionException("unknown argument: \'" + options[0] + "\' !");
        }
        throw OptionException("this command has only 1 option!");
    }
}


std::string WcCommand::getType()
{
    return "wc";
}

void WcCommand::execute()
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

    
    if (arguments[0][0] != '\'' && arguments[0][0] != '\"')
    {
        try
        {
            std::string file_input = IOHandler::readFile(arguments[0]);
            arguments[0] = file_input;
        }
        catch (const FileException& e)
        {
            std::cerr << "File error: " << e.what() << std::endl;
            return;
        }
        catch (const std::exception& e)
        {
            std::cerr << "An error occurred: " << e.what() << std::endl;
            return;
        }
    } 
    else
    {
        arguments[0] = arguments[0].substr(1, arguments[0].size()-2);
    }

    if (options[0] == "-c")
    {
        std::cout << arguments[0].size() << std::endl;
    }
    if (options[0] == "-w")
    {
        int i = 0, counter = 0;
        char last = 'a';
        arguments[0] += " ";
        while (i < arguments[0].size())
        {
            if (!std::isspace(last) && std::isspace(arguments[0][i]))
                counter++;
            last = arguments[0][i];
            i++;
        }
        std::cout << counter << std::endl;
    }

}



