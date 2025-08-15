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


Command* Parser::parse()
{
    seperateOnWhitespaces();

    semanticFlowAnalysis();
    syntaxTokenAnalysis();
    semanticTokenAnalysis();

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

void Parser::semanticTokenAnalysis()
{
    if (_is_pipeline_cmd)
        return;

    bool has_input_redirect = false, has_output_redirect = false, has_args = false, has_opt = false;

    for (int i = 0; i < _cmd_tokens.size(); i++)
    {
        switch (_cmd_tokens[i]->type())
        {
            case Option:
                has_opt = true;
                if (has_input_redirect)
                    throw SyntaxException(InRedirect);
                if (has_output_redirect)
                    throw SyntaxException(OutRedirect);
                if (has_args)
                    throw SyntaxException(Argument);
                break;
            case Argument:
                has_args = true;
                if (has_input_redirect)
                    throw SyntaxException(InRedirect);
                if (has_output_redirect)
                    throw SyntaxException(OutRedirect);
                break;
            case InRedirect:
                has_input_redirect = true;
                break;
            case OutRedirect:
                has_output_redirect = true;
                break;
        }
    }

}

void Parser::semanticFlowAnalysis()
{
    bool has_input_redirect = false, has_output_redirect = false, has_args = false;

    for (int i = 0; i < _cmd_tokens.size(); i++)
    {
        TokenType curr_type = _cmd_tokens[i]->type();
        if (curr_type == Argument)
            has_args = true;
        else if (curr_type == InRedirect)
        {
            if (has_input_redirect)
                throw SemanticFlowException(true);

            has_input_redirect = true;
        }
        else if (curr_type == OutRedirect)
        {
            if (has_output_redirect)
                throw SemanticFlowException(false);

            has_output_redirect = true;
        }
        else if (curr_type == CommandName)
        {
            _is_pipeline_cmd = true;
        }
    }

    if (has_args && has_input_redirect && !_is_pipeline_cmd)
        throw SemanticFlowException(true);
}

void Parser::syntaxTokenAnalysis()
{
    std::vector<int> errs, temp;

    for (int i = 0; i < _cmd_tokens.size(); i++)
    {
        temp = _cmd_tokens[i]->checkToken();

        errs.insert(errs.end(), temp.begin(), temp.end());
    }
    
    if (errs.size() != 0)
        throw SyntaxException(_original_line, errs);
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
    _cmd_tokens.insert(_cmd_tokens.begin(), _command_token);

    int num_of_redirects = (_input_redirect != NULL) + (_output_redirect != NULL);

    if (_output_redirect == NULL)
    {
        _output_redirect = new StdOutStream();
    }

    std::vector<Token*> curr_tokens;
    Command* curr_cmd = NULL, *next_cmd = NULL;

    CommandInStream *curr_in_str;
    OutStream *curr_out_str = _output_redirect;


    for (int i = _cmd_tokens.size()-1 - num_of_redirects; i >= 0; i--)
    {
        curr_tokens.insert(curr_tokens.begin(), _cmd_tokens[i]);
        
        if (_cmd_tokens[i]->type() == CommandName && i != 0)
        {
            curr_in_str = new CommandInStream();
            Parser pipe_parser = Parser(curr_tokens, curr_in_str, curr_out_str);

            curr_cmd = pipe_parser.parsePipelineCommand();
            curr_cmd->setNextCommand(next_cmd);

            curr_out_str = new CommandOutStream(curr_in_str);

            next_cmd = curr_cmd;

            curr_tokens.clear();
        }
        else if (_cmd_tokens[i]->type() == CommandName && i == 0)
        {
            CommandOutStream *out_stream = new CommandOutStream(curr_in_str);
            Parser pipe_parser = Parser(curr_tokens, _input_redirect, out_stream);
            curr_cmd = pipe_parser.parsePipelineCommand();
            curr_cmd->setNextCommand(next_cmd);
        }

        if (curr_cmd != NULL && !curr_cmd->hasOutputStream())
        {
            throw PipelineException(_cmd_tokens[i]->value());
        }
    }

    return curr_cmd;
}

Parser::Parser(std::vector<Token*> tokens, InputStream* in_stream, OutStream* out_stream)
{
    _command_token = tokens[0];
    _cmd_tokens.assign(tokens.begin() + 1, tokens.end());
    _input_redirect = in_stream;
    _output_redirect = out_stream;
}

Command* Parser::parsePipelineCommand()
{
    classifyTokens();

    if (_input_redirect == NULL)
        _input_redirect = new ArgInStream(_args);

    if (_input_redirect->getType() == InputStreamType::CommandInStream)
    {
        CommandInStream* command_in_stream = dynamic_cast<CommandInStream*>(_input_redirect);
        for (int i = 0; i < _args.size(); i++)
        {
            command_in_stream->addArgs(_args[i]);
        }
    }

    createCommand();

    if (!_final_command->hasOutputStream())
        throw PipelineException(_command_token->value());

    return _final_command;    
}
