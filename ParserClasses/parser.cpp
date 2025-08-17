#include <iostream>
#include <string>
#include <vector>
#include "../ExceptionClasses/exception.h"
#include "parser.h"
#include "../CommandClasses/echocommand.h"
#include "../CommandClasses/timecommand.h"
#include "../CommandClasses/datecommand.h"
#include "../CommandClasses/touchcommand.h"
#include "../CommandClasses/wccommand.h"
#include "../CommandClasses/exitcommand.h"
#include "../CommandClasses/headcommand.h"
#include "../CommandClasses/promptcommand.h"
#include "../CommandClasses/rmcommand.h"
#include "../CommandClasses/trcommand.h"
#include "../CommandClasses/trunicatecommand.h"
#include "../CommandClasses/batchcommand.h"
#include "../config.h"

#include "../TokenClasses/commandtoken.h"

#include "../StreamClasses/InStream/arginstream.h"
#include "../StreamClasses/InStream/fileinstream.h"
#include "../StreamClasses/InStream/stdinstream.h"
#include "../StreamClasses/InStream/inputstream.h"

#include "../StreamClasses/OutStream/fileoutstream.h"
#include "../StreamClasses/OutStream/stdoutstream.h"
#include "../StreamClasses/OutStream/commandoutstream.h"

#include "validitychecker.h"
#include "pipelineparser.h"

Command* Parser::parse()
{
    seperateOnWhitespaces();

    ValidityChecker checker(_cmd_tokens, _original_line);
    checker.checkAll();

    classifyTokens();
    if (_is_pipeline_cmd)
    {
        return createPipeline();
    }

    createCommand();
    return _final_command;
}

Parser::Parser(std::string &line)
{
    _original_line = line;
    _is_pipeline_cmd = false;
    _input_redirect = NULL;
    _output_redirect = NULL;
}

void Parser::seperateOnWhitespaces()
{
    std::vector<std::string> tokens;
    std::vector<int> token_pos_in_line;

    if (_original_line.length() > MAXLINELEN)
        _original_line = _original_line.substr(0, MAXLINELEN);

    char curr_segment = '*', curr_ch;
    std::string curr_str = "";

    for (int i = 0; i < _original_line.length(); i++)
    {
        curr_ch = _original_line[i];
        if (curr_ch == '\t' || curr_ch == '\n')
            curr_ch = ' ';

        if (curr_ch == '|' && (curr_segment == ' ' || curr_segment == '*'))
        {
            if (curr_str != "")
            {
                tokens.push_back(curr_str);
                token_pos_in_line.push_back(i - curr_str.length());
                curr_str = "";
            }
            tokens.push_back("|");
            token_pos_in_line.push_back(i);
            curr_segment = '*';
            continue;
        }

        if ((curr_ch == '\'' || curr_ch == '\"' || curr_ch == ' ') && curr_ch == curr_segment)
        {
            if (curr_ch != ' ')
                curr_str += _original_line[i];

            if (curr_str != "")
            {
                tokens.push_back(curr_str);
                token_pos_in_line.push_back(i - curr_str.length() + (curr_ch != ' '));
                curr_str = "";
            }

            curr_segment = '*';
            continue;
        }
        else if (curr_segment == '*')
        {
            if (curr_ch == '\'' || curr_ch == '\"')
                curr_segment = curr_ch;
            else if (curr_ch != ' ')
                curr_segment = ' ';
            else
                continue;
        }

        curr_str += _original_line[i];
    }

    if (curr_str != "")
    {
        tokens.push_back(curr_str);
        token_pos_in_line.push_back(_original_line.length() - curr_str.length());
    }

    if (tokens.size() == 0)
        return;

    tokenize(tokens, token_pos_in_line);
}

void Parser::tokenize(std::vector<std::string> &tokens, std::vector<int> &token_indx)
{
    _command_token = new CommandToken(tokens[0], token_indx[0]);
    for (int i = 1; i < tokens.size(); i++)
    {
        if (tokens[i] == "<" || tokens[i] == ">>" || tokens[i] == ">" || tokens[i] == "|")
        {
            if (i + 1 == tokens.size())
                throw SemanticFlowException(tokens[i]);
            
            _cmd_tokens.push_back(Token::createToken(tokens[i], token_indx[i], tokens[i+1], token_indx[i+1]));
            i++;
        }
        else if (tokens[i].length() > 1 && (tokens[i][0] == '>' || tokens[i][0] == '<'))
        {
            _cmd_tokens.push_back(Token::createToken(tokens[i], token_indx[i]));
        }
        else
        {
            _cmd_tokens.push_back(Token::createToken(tokens[i], token_indx[i]));
        }
        if (_cmd_tokens[_cmd_tokens.size()-1]->type() == CommandName)
            _is_pipeline_cmd = true;
    }
}

void Parser::classifyTokens()
{
    for (int i = 0; i < _cmd_tokens.size(); i++)
    {
        switch (_cmd_tokens[i]->type())
        {
            case Argument:
                _args.push_back(_cmd_tokens[i]);
                break;
            case Option:
                _options.push_back(_cmd_tokens[i]);
                break;
            case InRedirect:
                _input_redirect = new FileInStream(_cmd_tokens[i]->value());
                break;
            case OutRedirect:
                _output_redirect = new FileOutStream(_cmd_tokens[i]->value(), _cmd_tokens[i]->subType() == OutAppend);
                break;
        }
    }
}

void Parser::print()
{
    _command_token->print();
    _input_redirect->print();
    _output_redirect->print();

    std::cout << "Arguments: " << std::endl;
    for (const auto& arg : _args)
        arg->print();
    std::cout << std::endl;

    std::cout << "Options: " << std::endl;
    for (const auto& opt : _options)
        opt->print();
    std::cout << std::endl;

    std::cout << "Tokens: " << std::endl;
    for (const auto& token : _cmd_tokens)
        token->print();
}

void Parser::createCommand()
{
    _final_command = NULL;

    if (_input_redirect == NULL)
    {
        _input_redirect = new ArgInStream(_args);
    }

    if (_output_redirect == NULL)
    {
        _output_redirect = new StdOutStream();
    }

    std::string command_name = _command_token->value();

    if (command_name == EchoCommand::getType())
    {
        _final_command =  new EchoCommand(_input_redirect, _output_redirect, _options);
    }
    if (command_name == TimeCommand::getType())
    {
        _final_command =  new TimeCommand(_input_redirect, _output_redirect, _options);
    }
    if (command_name == DateCommand::getType())
    {
        _final_command =  new DateCommand(_input_redirect, _output_redirect, _options);
    }
    if (command_name == TouchCommand::getType())
    {
        _final_command =  new TouchCommand(_input_redirect, _output_redirect, _options);
    }
    if (command_name == WcCommand::getType())
    {
        _final_command =  new WcCommand(_input_redirect, _output_redirect, _options);
    }
    if (command_name == ExitCommand::getType())
    {
        _final_command =  new ExitCommand(_input_redirect, _output_redirect, _options);
    }
    if (command_name == HeadCommand::getType())
    {
        _final_command =  new HeadCommand(_input_redirect, _output_redirect, _options);
    }
    if (command_name == PromptCommand::getType())
    {
        _final_command =  new PromptCommand(_input_redirect, _output_redirect, _options);
    }
    if (command_name == RmCommand::getType())
    {
        _final_command =  new RmCommand(_input_redirect, _output_redirect, _options);
    }
    if (command_name == TrCommand::getType())
    {
        _final_command =  new TrCommand(_input_redirect, _output_redirect, _options);
    }
    if (command_name == TrunicateCommand::getType())
    {
        _final_command =  new TrunicateCommand(_input_redirect, _output_redirect, _options);
    }
    if (command_name == BatchCommand::getType())
    {
        _final_command =  new BatchCommand(_input_redirect, _output_redirect, _options);
    }

    if (_final_command == NULL)
        throw CommandException(command_name);
}

Command* Parser::createPipeline() 
{
    std::vector<std::vector<Token*>> pipeline_command;
    pipeline_command.push_back({_command_token});

    int curr_command_num = 0;
    for (int i = 0; i < _cmd_tokens.size(); i++)
    {

        if (_cmd_tokens[i]->type() == CommandName)
        {
            curr_command_num++;
            pipeline_command.push_back({_cmd_tokens[i]});
            continue;
        }

        pipeline_command[curr_command_num].push_back(_cmd_tokens[i]);
    }

    if (pipeline_command.size() == 0)
        throw std::runtime_error("Something is really wrong!");

    std::vector<InputStream*> command_in_stream = {NULL};
    std::vector<OutStream*> command_out_stream;

    for (int i = 1; i < pipeline_command.size(); i++)
    {
        command_in_stream.push_back(new CommandInStream());
    }
    for (int i = 0; i < pipeline_command.size()-1; i++)
    {
        command_out_stream.push_back(new CommandOutStream(dynamic_cast<CommandInStream*>(command_in_stream[i+1])));
    }
    command_out_stream.push_back(NULL);

    PipelineParser* p = new PipelineParser(pipeline_command[0], command_in_stream[0], command_out_stream[0]);
    Command* first_command = p->parse();
    Command* prev_command = first_command;

    for (int i = 1; i < pipeline_command.size(); i++)
    {
        delete p;
        p = new PipelineParser(pipeline_command[i], command_in_stream[i], command_out_stream[i]);
        Command* curr_cmd = p->parse();
        prev_command->setNextCommand(curr_cmd);
        prev_command = curr_cmd;
    }

    return first_command;
}

Parser::Parser() {
    _command_token = nullptr;
    _input_redirect = nullptr;
    _output_redirect = nullptr;
    _final_command = nullptr;
}
