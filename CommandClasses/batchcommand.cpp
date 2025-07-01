#include "batchcommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohelper.h"
#include "../HelperClasses/parser.h"

void BatchCommand::isValid() 
{
    if (arguments.size() > 1)
    {
        throw ArgumentException(1, arguments.size());
    }
    if (options.size() != 0)
    {        
        throw OptionException(0, options.size());
    }
}


std::string BatchCommand::getType()
{
    return "batch";
}

std::string BatchCommand::getOutput()
{
    if (arguments.size() == 0)
    {
        std::string cmd_input = io.getInput();
        arguments.push_back("\"" + cmd_input + "\"");
    }

    if (std::isalpha(arguments[0][0]))
    {
        std::string file_input = io.readFile(arguments[0]);
        arguments[0] = file_input;
    }
    else
    {
        arguments[0] = arguments[0].substr(1, arguments[0].size()-2);
    }

    std::vector<std::string> command_lines;
    int begin = 0;
    for (int i = 0; i <= arguments[0].size(); i++)
    {
        if (i == arguments[0].size() || arguments[0][i] == '\n')
        {
            if (begin != i)
                command_lines.push_back(arguments[0].substr(begin, i - begin));
            begin = i+1;
        }
    }

    for (int i = 0; i < command_lines.size(); i++)
    {
        try
        {
            Command* curr = Parser::parse(command_lines[i]);
            curr->execute();
            
        }
        catch (const ArgumentException& e)
        {
            std::cerr << "Argument Error: " << e.what() << std::endl;
        }
        catch (const OptionException& e)
        {
            std::cerr << "Option Error: " << e.what() << std::endl;
        }
        catch (const FileException& e)
        {
            std::cerr << "File Error: " << e.what() << std::endl;
        }
        catch (const SyntaxException& e)
        {
            std::cerr << "Syntax Error: " << e.what() << std::endl;
        }
        catch (const SemanticFlowException& e)
        {
            std::cerr << "Flow Error: " << e.what() << std::endl;
        }
        catch (const CommandException& e)
        {
            std::cerr << "Command Error: " << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return "";
        }
    }
    return "";
}



