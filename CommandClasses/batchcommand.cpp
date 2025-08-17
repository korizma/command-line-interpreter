#include "batchcommand.h"
#include <iostream>
#include <string>
#include "../HelperClasses/iohelper.h"
#include "../ParserClasses/parser.h"
#include "../StreamClasses/InStream/arginstream.h"
#include "../StreamClasses/InStream/commandinstream.h"
#include "../StreamClasses/OutStream/commandoutstream.h"

BatchCommand::~BatchCommand()
{
    
}


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
    return _args.empty() && !_nested_call;
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
    _nested_call = true;
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

    CommandInStream* batch_in_stream = new CommandInStream({}); 

    for (int i = 0; i < command_lines.size(); i++)
    {
        std::string error_message = "";
        try
        {
            Parser p = Parser(command_lines[i]);
            Command* curr = p.parse();

            CommandOutStream* batch_out_stream = new CommandOutStream(batch_in_stream);
            curr->setOutputStream(batch_out_stream);

            BatchCommand* casted = dynamic_cast<BatchCommand*>(curr);

            if (casted && casted->inputCanBeOverridden())
            {
                casted->setToNested();
                
                std::string commands = "";
                for (int j = i+1; j < command_lines.size(); j++)
                    commands += command_lines[j] + "\n";

                commands = "\'" + commands + "\'";
                InputStream* nested_input = new ArgInStream({new ArgumentToken(commands, 0)});

                casted->setInputStream(nested_input);
                casted->execute();

                delete casted;
                break;
            }

            curr->execute();
            delete curr;
        }
        catch (const ArgumentException& e)
        {
            error_message = "Argument Error: " + std::string(e.what());
        }
        catch (const OptionException& e)
        {
            error_message = "Option Error: " + std::string(e.what());
        }
        catch (const FileException& e)
        {
            error_message = "File Error: " + std::string(e.what());
        }
        catch (const SyntaxException& e)
        {
            error_message = "Syntax Error: " + std::string(e.what());
        }
        catch (const SemanticFlowException& e)
        {
            error_message = "Flow Error: " + std::string(e.what());
        }
        catch (const CommandException& e)
        {
            error_message = "Command Error: " + std::string(e.what());
        }
        catch (const PipelineException& e)
        {
            error_message = "Pipeline Error: " + std::string(e.what());
        }
        catch (const std::exception& e)
        {
            error_message = "Unknown Error: " + std::string(e.what());
        }

        if (!error_message.empty())
        {
            CommandOutStream* error_out_stream = new CommandOutStream(batch_in_stream);
            error_out_stream->writeStream(error_message);
        }
    }

    std::string final_output = "";
    std::vector<Token*> command_outputs = batch_in_stream->readStream();

    for (int i = command_outputs.size()-1; i >= 0; i--)
    {
        final_output += command_outputs[i]->value() + "\n";
    }

    return final_output;
}

BatchCommand::BatchCommand(InputStream* inputStream, OutStream* outputStream, const std::vector<Token*>& options)
    : Command(inputStream, outputStream, options)
{
    _nested_call = false;

    ArgInStream *casted = dynamic_cast<ArgInStream*>(inputStream);
    if (casted)
    {
        _input_can_be_overridden = casted->getArgCount() == 0;
    }
    else
    {
        _input_can_be_overridden = false;
    }
}


bool BatchCommand::inputCanBeOverridden() const
{
    return _input_can_be_overridden;
}