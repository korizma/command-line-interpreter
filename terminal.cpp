#include "terminal.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include "CommandClasses/command.h"
#include "HelperClasses/parser.h"
#include "config.h"


Terminal::Terminal()
{
    char buffer[500];
    ::getcwd(buffer, sizeof(buffer));
    std::string current_dir(buffer);
    path = current_dir;
    ready_sign = PATHSIGN;
}

Terminal* Terminal::getInstance()
{
    static Terminal instance;
    return &instance;
}

std::string Terminal::getPath()
{
    return path;
}

void Terminal::run()
{
    Terminal *term = getInstance();
    term->start();
}

void Terminal::start()
{
    std::string line;
    Command *curr_command;

    while (true)
    {
        std::cout << ready_sign;
        line = io.getLine();
        try 
        {
            Parser p = Parser(line);
            curr_command = p.parse();
            curr_command->execute();
            delete curr_command;
        }
        catch (const ArgumentException& e)
        {
            std::cerr << "Argument Error: " << e.what() << std::endl; 
        }
        catch (const OptionException& e)
        {
            std::cerr << "Option Error: " << e.what() << std::endl; 
        }
        catch (const SyntaxException& e)
        {
            std::cerr << "Syntax Error: " << e.what() << std::endl; 
        }
        catch (const CommandException& e)
        {
            std::cerr << "Command Error: " << e.what() << std::endl; 
        }
        catch (const SemanticFlowException& e)
        {
            std::cerr << "Flow Error: " << e.what() << std::endl; 
        }
        catch (const FileException& e)
        {
            std::cerr << "File Error: " << e.what() << std::endl; 
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl; 
        }
    }
}


void Terminal::changeSign(std::string new_sign)
{
    ready_sign = new_sign;
}

