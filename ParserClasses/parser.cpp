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
    _input_redirect = _output_redirect = NULL;
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
    }
}

void Parser::semanticTokenAnalysis()
{
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
                _input_redirect = _cmd_tokens[i];
                break;
            case OutRedirect:
                _output_redirect = _cmd_tokens[i];
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

    InputStream *input_stream;
    OutStream *output_stream;

    if (_input_redirect)
    {
        input_stream = new FileInStream(_input_redirect->value());
    }
    else 
    {
        input_stream = new ArgInStream(_args);
    }

    if (_output_redirect)
    {
        output_stream = new FileOutStream(_output_redirect->value(), _output_redirect->subType() == OutAppend);
    }
    else
    {
        output_stream = new StdOutStream();
    }

    std::string command_name = _command_token->value();

    if (command_name == EchoCommand::getType())
    {
        _final_command =  new EchoCommand(input_stream, output_stream, _options);
    }
    if (command_name == TimeCommand::getType())
    {
        _final_command =  new TimeCommand(input_stream, output_stream, _options);
    }
    if (command_name == DateCommand::getType())
    {
        _final_command =  new DateCommand(input_stream, output_stream, _options);
    }
    if (command_name == TouchCommand::getType())
    {
        _final_command =  new TouchCommand(input_stream, output_stream, _options);
    }
    if (command_name == WcCommand::getType())
    {
        _final_command =  new WcCommand(input_stream, output_stream, _options);
    }
    if (command_name == ExitCommand::getType())
    {
        _final_command =  new ExitCommand(input_stream, output_stream, _options);
    }
    if (command_name == HeadCommand::getType())
    {
        _final_command =  new HeadCommand(input_stream, output_stream, _options);
    }
    if (command_name == PromptCommand::getType())
    {
        _final_command =  new PromptCommand(input_stream, output_stream, _options);
    }
    if (command_name == RmCommand::getType())
    {
        _final_command =  new RmCommand(input_stream, output_stream, _options);
    }
    if (command_name == TrCommand::getType())
    {
        _final_command =  new TrCommand(input_stream, output_stream, _options);
    }
    if (command_name == TrunicateCommand::getType())
    {
        _final_command =  new TrunicateCommand(input_stream, output_stream, _options);
    }
    // if (command_name == BatchCommand::getType())
    // {
    //     _final_command =  new BatchCommand(input_stream, output_stream, _options);
    // }

    if (_final_command == NULL)
        throw CommandException(command_name);
}

Command* Parser::createPipeline() 
{
    // for (int i = 0; i < cmd_tokens.size()-1; i++)
    //     if (cmd_tokens[i]->type() == cmd_tokens[i+1]->type() && cmd_tokens[i]->type() == PipeSign)
    //         throw SyntaxException("Invalid pipeline creation");

    // std::vector<Token*> curr_tokens;

    // std::vector<Command*> finished_commands;

    // bool first_command_processed = false;


    // for (int i = 0; i <= cmd_tokens.size(); i++)
    // {
    //     if (i == cmd_tokens.size() ||cmd_tokens[i]->type() == PipeSign)
    //     {

    //         if (!first_command_processed)
    //         {
    //             Parser pipeline_parse = Parser(command_name, curr_tokens, true, input_redirect, output_redirect, output_redirect_append);
    //             finished_commands.push_back(pipeline_parse.parsePipelineCmd());
    //             first_command_processed = true;
    //         }
    //         else
    //         {
    //             command_name = curr_tokens[0]->value();
    //             curr_tokens.erase(curr_tokens.begin());
    //             Parser pipeline_parse = Parser(command_name, curr_tokens, false, "", "", false);
    //             finished_commands.push_back(pipeline_parse.parsePipelineCmd());
    //         }


    //         curr_tokens = {};
            
    //         continue;
    //     }

    //     if (cmd_tokens[i]->type() != InRedirect && cmd_tokens[i]->type() != OutRedirect)
    //         curr_tokens.push_back(cmd_tokens[i]);

    // }

    // for (int i = 0; i < finished_commands.size()-1; i++)
    // {
    //     finished_commands[i]->setNext(finished_commands[i+1]);
    // }
    // return finished_commands[0];
}



// Parser::Parser(const std::string cmd_name, std::vector<Token*> &tokens, bool first_command, std::string in_redirect, std::string out_redirect, bool out_append)
//     : command_name(cmd_name), cmd_tokens(tokens), is_first_in_pipeline(first_command), input_redirect(in_redirect), output_redirect(out_redirect), output_redirect_append(out_append)
// {
// }

Command* Parser::parsePipelineCmd()
{
    classifyTokens();

    createCommand();
    return _final_command;
}

