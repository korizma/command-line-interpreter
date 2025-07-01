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


IOHelper Parser::io;

Command* Parser::parse(const std::string& input)
{ 
    std::vector<std::string> tokens = tokenize(input); 

    
    bool input_redirect = false, pipeline = false;

    for (int i = 1; i < tokens.size(); i++)
    {
        if (tokens[i] == "|")
        {
            pipeline = true;
            break;
        }
        if (tokens[i][0] == '>')
        {
            input_redirect = true;
        }
    }

    if (pipeline)
        return createPipeline(tokens);

    std::vector<std::string> arguments, options;
    std::string command_type;
    classifyTokens(tokens, command_type, arguments, options);

    checkTokensSemantics(arguments);

    if (input_redirect)
    {
        tokenizeRedirect(arguments);
    }

    Command* komanda = Parser::createCommand(command_type, arguments, options);

    return komanda;
}

void Parser::tokenizeRedirect(std::vector<std::string>& args)
{
    std::string file_input = "";
    int i;
    for (i = 0; i < args.size(); i++)
        if (args[i][0] == '>')
            break;
    
    if (i == args.size())
        throw std::out_of_range("it should have input redirect file there!");

    file_input = args[i].substr(1, args[i].size()-1);
    args.erase(args.begin() + i);

    std::string file_content = io.readFile(file_input);
    for (i = 0; i < file_content.size(); i++)
        if (file_content[i] == '\n')
            break;
    
    if (i != file_content.size())
        file_content.erase(file_content.begin() + i, file_content.end());

    std::vector<std::string> tokens = tokenize(file_content, true);

    for (i = 0; i < tokens.size(); i++)
        args.push_back(tokens[i]);
}

std::vector<int> Parser::checkTokenRedirectSyntax(const std::string& token, const int& pos_in_line)
{
    std::vector<int> indx_errors;
    
    if (std::isalpha(token[0]))
    {
        bool has_dot = false;
        for (int i = 1; i < token.size(); i++)
        {
            if (!(std::isalpha(token[i]) || (!has_dot && token[i] == '.')))
                indx_errors.push_back(i + pos_in_line);
            if (token[i] == '.')
                has_dot = true;
        }
    }
    else if (token[0] == '\'' || token[0] == '\"')
    {
        if (token.size() == 1)
        {
            indx_errors.push_back(pos_in_line);
        }
        else if (token[0] != token[token.size()-1])
        {
            indx_errors.push_back(pos_in_line);
            indx_errors.push_back(pos_in_line + token.size()-1);
        }
    }
    else 
    {
        indx_errors.push_back(pos_in_line);
    }
    return indx_errors;
}

std::vector<std::string> Parser::tokenize(const std::string& input, const bool& is_redirect)
{
    std::string line = input;
    if (line.size() > 512)
        line.erase(input.begin() + 512, input.end());

    std::vector<std::string> tokens;
    char curr_par = ' ';
    if (line[0] == '\"' || line[0] == '\'')
        curr_par = line[0];
    std::string curr_token = "";
    curr_token += line[0];

    for (int i = 1; i <= line.size(); i++)
    {
        if (i == line.size() || (curr_par == ' ' && (line[i] == ' ' || line[i] == '\t')))
        {
            if (curr_token.size() != 0)
            {
                std::vector<int> errs;
                if (!is_redirect) 
                    errs = checkTokenSyntax(curr_token, i - curr_token.size());
                else
                    errs = checkTokenRedirectSyntax(curr_token, i - curr_token.size());

                if (errs.size() != 0)
                    throw SyntaxException(line, errs);
                
                tokens.push_back(curr_token);
            }
            curr_token = "";
            continue;
        }

        curr_token += line[i];

        if (curr_par != ' ' && curr_par == line[i])
            curr_par = ' ';
        else
            if (curr_par == ' ' && (line[i] == '\'' || line[i] == '\"'))
                curr_par = line[i];
    }

    return tokens;
}

std::vector<int> Parser::checkTokenSyntax(const std::string& token, const int& pos_in_line)
{
    std::vector<int> indx_errors;
    if (pos_in_line == 0) // provera sintakse za komandu
    {
        for (int i = 0; i < token.size(); i++)
        {
            if (!std::isalpha(token[i]))
                indx_errors.push_back(i + pos_in_line);
        }
    }
    else if (token[0] == '-')
    {
        if (token.size() == 1)
            indx_errors.push_back(pos_in_line);
        else
            for (int i = 1; i < token.size(); i++)
                if (!std::isalnum(token[i]))
                    indx_errors.push_back(i + pos_in_line);
    }
    else if (std::isalpha(token[0]))
    {
        bool has_dot = false;
        for (int i = 1; i < token.size(); i++)
        {
            if (!(std::isalpha(token[i]) || (!has_dot && token[i] == '.')))
                indx_errors.push_back(i + pos_in_line);
            if (token[i] == '.')
                has_dot = true;
        }
    }
    else if (token[0] == '\'' || token[0] == '\"')
    {
        if (token.size() == 1)
        {
            indx_errors.push_back(pos_in_line);
        }
        else if (token[0] != token[token.size()-1])
        {
            indx_errors.push_back(pos_in_line);
            indx_errors.push_back(pos_in_line + token.size()-1);
        }
    }
    else 
    {
        if (token != "|" && token != "<" && token != "<<" && token != ">")
            indx_errors.push_back(pos_in_line);
    }
    return indx_errors;
}

Command* Parser::createCommand(const std::string& cmd_name, const std::vector<std::string>& arguments, const std::vector<std::string>& options, Command* next) 
{
    if (cmd_name == EchoCommand::getType())
    {
        return new EchoCommand(arguments, options, next);
    }
    if (cmd_name == TimeCommand::getType())
    {
        return new TimeCommand(arguments, options, next);
    }
    if (cmd_name == DateCommand::getType())
    {
        return new DateCommand(arguments, options, next);
    }
    if (cmd_name == TouchCommand::getType())
    {
        return new TouchCommand(arguments, options, next);
    }
    if (cmd_name == WcCommand::getType())
    {
        return new WcCommand(arguments, options, next);
    }
    if (cmd_name == ExitCommand::getType())
    {
        return new ExitCommand(arguments, options, next);
    }
    if (cmd_name == HeadCommand::getType())
    {
        return new HeadCommand(arguments, options, next);
    }
    if (cmd_name == PromptCommand::getType())
    {
        return new PromptCommand(arguments, options, next);
    }
    if (cmd_name == RmCommand::getType())
    {
        return new RmCommand(arguments, options, next);
    }
    if (cmd_name == TrCommand::getType())
    {
        return new TrCommand(arguments, options, next);
    }
    if (cmd_name == TrunicateCommand::getType())
    {
        return new TrunicateCommand(arguments, options, next);
    }
    if (cmd_name == BatchCommand::getType())
    {
        return new BatchCommand(arguments, options, next);
    }

    throw CommandException(cmd_name);
}

void Parser::checkTokensSemantics(std::vector<std::string>& args, const bool& pipeline)
{
    bool reg_input = false, redirect_input = false, redirect_output = false;

    for (int i = 0; i < args.size(); i++)
    {
        if  (isalpha(args[0][0]) || args[0][0] == '\'' || args[0][0] == '\"')
            reg_input = true;
        if (args[0][0] == '<')
            if (redirect_output)
                throw SemanticFlowException(false);
            else
                redirect_output = true;
        if (args[0][0] == '>')
            if (redirect_input)
                throw SemanticFlowException(true);
            else
                redirect_input = true;
    }

    if (reg_input && redirect_input)
        throw SemanticFlowException(true);

    if (pipeline && redirect_output)
        throw SemanticFlowException(false);
}

Command* Parser::createPipeline(std::vector<std::string>& tokens)
{
    std::vector<std::vector<std::string>> command_tokens;
    command_tokens.push_back({});
    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i] == "|")
        {
            command_tokens.push_back({});
            continue;
        }

        command_tokens[command_tokens.size() - 1].push_back(tokens[i]);
    }

    Command *curr = NULL;

    for (int i = command_tokens.size()-1; i >= 0; i--)
    {
        std::vector<std::string> arguments, options;
        std::string command_type; 
        bool input_redirect = false;
        for (int j = 0; j < command_tokens[i].size(); j++)
                if (command_tokens[i][j][0] == '>')
                {
                    input_redirect = true;
                    break;
                }
        classifyTokens(command_tokens[i], command_type, arguments, options);
        checkTokensSemantics(arguments, i != 0);

        if (input_redirect)
            tokenizeRedirect(arguments);

        curr = createCommand(command_type, arguments, options, curr);
    }
    return curr;
}


void Parser::classifyTokens(const std::vector<std::string>& tokens, std::string& cmd_name, std::vector<std::string>& args, std::vector<std::string>& options)
{
    cmd_name = tokens[0];
    for (int i = 1; i < tokens.size(); i++)
    {
        if (tokens[i][0] == '-')
            options.push_back(tokens[i]);
        else
        {
            if (tokens[i] == "<" || tokens[i] == "<<" || tokens[i] == ">")
                if (i == tokens.size()-1 || !isalpha(tokens[i+1][0]))
                    throw SemanticFlowException(tokens[i]);
                else
                {
                    std::string new_arg = tokens[i] + tokens[i+1];
                    i++;
                    args.push_back(new_arg);
                }
            else
                args.push_back(tokens[i]);
        }
    }
}

