#include "batchcommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohelper.h"
#include "../ParserClasses/parser.h"

void BatchCommand::isValid() 
{
    if (_args.size() != 1)
    {
        throw ArgumentException(1, _args.size());
    }
    if (_options.size() != 0)
    {        
        throw OptionException(0, _options.size());
    }
}

bool BatchCommand::needsInput() const
{
    return _args.empty() && !nested_call;
}

bool BatchCommand::acceptsFileArgRead() const
{
    return true;
}

std::string BatchCommand::getType()
{
    return "batch";
}

void BatchCommand::setToNested()
{
    nested_call = true;
}

std::string BatchCommand::getOutput()
{
    std::vector<std::string> command_lines;
    int begin = 0;

    std::string text = _args[0]->value();

    for (int i = 0; i <= text.size(); i++)
    {
        if (i == text.size() || text[i] == '\n')
        {
            if (begin != i)
                command_lines.push_back(_args[0]->value().substr(begin, i - begin));
            begin = i+1;
        }
    }

    for (int i = 0; i < command_lines.size(); i++)
    {
        try
        {
            Parser p = Parser(command_lines[i]);
            Command* curr = p.parse();
            BatchCommand* casted = dynamic_cast<BatchCommand*>(curr);

            if (casted)
            {
                casted->setToNested();
                
                std::string commands = "";
                for (int j = i+1; j < command_lines.size(); j++)
                    commands += command_lines[j] + "\n";
                
                commands = "\'" + commands + "\'";
                
                casted->acceptNestedArg(commands);
                casted->execute();
                break;
            }

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


void BatchCommand::acceptNestedArg(std::string &commands)
{
    _args.push_back(new ArgumentToken(commands, 0));
}

BatchCommand::BatchCommand(InputStream* inputStream, OutStream* outputStream, const std::vector<Token*>& options)
    : Command(inputStream, outputStream, options)
{
    nested_call = false;
}
