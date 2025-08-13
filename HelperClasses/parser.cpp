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
#include "tokenchecker.h"

Command* Parser::parse()
{
    seperateOnWhitespaces();



    semanticFlowAnalysis();
    syntaxTokenAnalysis();
    semanticTokenAnalysis();

    classifyTokens();

    if (input_redirect != "" && !is_pipeline_cmd)
    {
        readRedirect();

        seperateOnWhitespaces();

        syntaxTokenAnalysis();

        checkRedirectTokens();

        classifyTokens();
    }

    if (is_pipeline_cmd)
    {
        return createPipeline();
    }

    

    createCommand();
    return final_command;
}

Parser::Parser(std::string &line)
{
    original_line = line;
    is_pipeline_cmd = has_regular_args = output_redirect_append = false;
    input_redirect = output_redirect = "";
}

void Parser::seperateOnWhitespaces()
{
    std::vector<std::string> tokens;
    std::vector<int> token_pos_in_line;

    if (original_line.length() > MAXLINELEN)
        original_line = original_line.substr(0, MAXLINELEN);

    char curr_segment = '*', curr_ch;
    std::string curr_str = "";

    for (int i = 0; i < original_line.length(); i++)
    {
        curr_ch = original_line[i];
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
                curr_str += original_line[i];

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

        curr_str += original_line[i];
    }

    if (curr_str != "")
    {
        tokens.push_back(curr_str);
        token_pos_in_line.push_back(original_line.length() - curr_str.length());
    }

    if (tokens.size() == 0)
        return;
    
    if (command_name == "")
    {   
        command_name = tokens[0];
        tokens.erase(tokens.begin());
        token_pos_in_line.erase(token_pos_in_line.begin());
    }

    tokenize(tokens, token_pos_in_line);
}

void Parser::tokenize(std::vector<std::string> &tokens, std::vector<int> &token_indx)
{
    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i] == "<" || tokens[i] == ">>" || tokens[i] == ">")
        {
            if (i+1 == tokens.size())
                throw SemanticFlowException(tokens[i]);

            cmd_tokens.push_back(new Token(tokens[i], token_indx[i], tokens[i+1], token_indx[i+1]));
            i++;
        }
        else
            cmd_tokens.push_back(new Token(tokens[i], token_indx[i]));
    }
}

void Parser::semanticTokenAnalysis()
{
    bool has_input_redirect = false, has_output_redirect = false, has_args = false, has_opt = false;

    for (int i = 0; i < cmd_tokens.size(); i++)
    {
        switch (cmd_tokens[i]->type())
        {
        case Arg:
            has_args = true;
            if (has_input_redirect)
                throw SyntaxException(InRedirect);
            if (has_output_redirect)
                throw SyntaxException(OutRedirect);
            if (has_opt)
                throw SyntaxException(Option);
            break;
        case Option:
            has_opt = true;
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
    bool read_from_redirect = input_redirect != "";
    bool has_input_redirect = false, has_output_redirect = false, has_args = false;

    for (int i = 0; i < cmd_tokens.size(); i++)
    {
        TokenType curr_type = cmd_tokens[i]->type();
        if (curr_type == Arg)
            has_args = true;
        else if (curr_type == InRedirect)
        {
            if (has_input_redirect || read_from_redirect)
                throw SemanticFlowException(true);

            has_input_redirect = true;
        }
        else if (curr_type == OutRedirect)
        {
            if (has_output_redirect || read_from_redirect)
                throw SemanticFlowException(false);

            has_output_redirect = true;
        }
        else if (curr_type == PipeSign)
        {
            if (read_from_redirect)
                throw PipelineException(input_redirect);

            is_pipeline_cmd = true;
        }
    }

    if (has_args && has_input_redirect && !is_pipeline_cmd)
        throw SemanticFlowException(true);
}

void Parser::syntaxTokenAnalysis()
{
    std::vector<int> errs, temp;

    for (int i = 0; i < cmd_tokens.size(); i++)
    {
        temp = cmd_tokens[i]->check();

        errs.insert(errs.end(), temp.begin(), temp.end());
    }
    
    if (errs.size() != 0)
        throw SyntaxException(original_line, errs);
}

void Parser::classifyTokens()
{
    for (int i = 0; i < cmd_tokens.size(); i++)
    {
        switch (cmd_tokens[i]->type())
        {
        case Arg:
            args.push_back(cmd_tokens[i]->value());
            break;
        case Option:
            options.push_back(cmd_tokens[i]->value());
            break;
        case InRedirect:
            input_redirect = cmd_tokens[i]->value();
            if (!cmd_tokens[i]->has_extra())
                input_redirect = input_redirect.substr(1, input_redirect.length()-1);
            break;
        case OutRedirect:
            output_redirect = cmd_tokens[i]->value();
            if (!cmd_tokens[i]->has_extra())
            {
                output_redirect = output_redirect.substr(1, output_redirect.length()-1);
                if (output_redirect[0] == '>')
                {
                    output_redirect_append = true;
                    output_redirect = output_redirect.substr(1, output_redirect.length()-1);
                }
            }
            else
            {
                output_redirect_append = cmd_tokens[i]->isAppendOutputRedirect();
            }
            break;
        }
    }
}

void Parser::print()
{
    std::cout << "Command name: " << command_name << std::endl;
    std::cout << "Input redirect: " << input_redirect << std::endl;
    std::cout << "Output redirect: " << output_redirect << std::endl;
    std::cout << "Output redirect append: " << (output_redirect_append ? "true" : "false") << std::endl;

    std::cout << "Arguments: ";
    for (const auto& arg : args)
        std::cout << arg << " ";
    std::cout << std::endl;

    std::cout << "Options: ";
    for (const auto& opt : options)
        std::cout << opt << " ";
    std::cout << std::endl;

    std::cout << "Tokens: " << std::endl;
    for (const auto& token : cmd_tokens)
        token->print();
}

void Parser::createCommand()
{
    final_command = NULL;
    if (command_name == EchoCommand::getType())
    {
        final_command =  new EchoCommand(args, options, output_redirect, output_redirect_append);
    }
    if (command_name == TimeCommand::getType())
    {
        final_command =  new TimeCommand(args, options, output_redirect, output_redirect_append);
    }
    if (command_name == DateCommand::getType())
    {
        final_command =  new DateCommand(args, options, output_redirect, output_redirect_append);
    }
    if (command_name == TouchCommand::getType())
    {
        final_command =  new TouchCommand(args, options, output_redirect, output_redirect_append);
    }
    if (command_name == WcCommand::getType())
    {
        final_command =  new WcCommand(args, options, output_redirect, output_redirect_append);
    }
    if (command_name == ExitCommand::getType())
    {
        final_command =  new ExitCommand(args, options, output_redirect, output_redirect_append);
    }
    if (command_name == HeadCommand::getType())
    {
        final_command =  new HeadCommand(args, options, output_redirect, output_redirect_append);
    }
    if (command_name == PromptCommand::getType())
    {
        final_command =  new PromptCommand(args, options, output_redirect, output_redirect_append);
    }
    if (command_name == RmCommand::getType())
    {
        final_command =  new RmCommand(args, options, output_redirect, output_redirect_append);
    }
    if (command_name == TrCommand::getType())
    {
        final_command =  new TrCommand(args, options, output_redirect, output_redirect_append);
    }
    if (command_name == TrunicateCommand::getType())
    {
        final_command =  new TrunicateCommand(args, options, output_redirect, output_redirect_append);
    }
    if (command_name == BatchCommand::getType())
    {
        final_command =  new BatchCommand(args, options, output_redirect, output_redirect_append);
    }

    if (final_command == NULL)
        throw CommandException(command_name);
}

Command* Parser::createPipeline() 
{
    for (int i = 0; i < cmd_tokens.size()-1; i++)
        if (cmd_tokens[i]->type() == cmd_tokens[i+1]->type() && cmd_tokens[i]->type() == PipeSign)
            throw SyntaxException("Invalid pipeline creation");

    std::vector<Token*> curr_tokens;

    std::vector<Command*> finished_commands;

    bool first_command_processed = false;


    for (int i = 0; i <= cmd_tokens.size(); i++)
    {
        if (i == cmd_tokens.size() ||cmd_tokens[i]->type() == PipeSign)
        {

            if (!first_command_processed)
            {
                Parser pipeline_parse = Parser(command_name, curr_tokens, true, input_redirect, output_redirect, output_redirect_append);
                finished_commands.push_back(pipeline_parse.parsePipelineCmd());
                first_command_processed = true;
            }
            else
            {
                command_name = curr_tokens[0]->value();
                curr_tokens.erase(curr_tokens.begin());
                Parser pipeline_parse = Parser(command_name, curr_tokens, false, "", "", false);
                finished_commands.push_back(pipeline_parse.parsePipelineCmd());
            }


            curr_tokens = {};
            
            continue;
        }

        if (cmd_tokens[i]->type() != InRedirect && cmd_tokens[i]->type() != OutRedirect)
            curr_tokens.push_back(cmd_tokens[i]);

    }

    for (int i = 0; i < finished_commands.size()-1; i++)
    {
        finished_commands[i]->setNext(finished_commands[i+1]);
    }
    return finished_commands[0];
}

void Parser::readRedirect() 
{
    IOHelper io = IOHelper();
    original_line = "\"" + io.readFile(input_redirect) + "\"";

    for (int i = 0; i < cmd_tokens.size(); i++)
        delete cmd_tokens[i];

    cmd_tokens.clear();
}

Parser::Parser(const std::string cmd_name, std::vector<Token*> &tokens, bool first_command, std::string in_redirect, std::string out_redirect, bool out_append)
    : command_name(cmd_name), cmd_tokens(tokens), is_first_in_pipeline(first_command), input_redirect(in_redirect), output_redirect(out_redirect), output_redirect_append(out_append)
{
}

Command* Parser::parsePipelineCmd()
{
    classifyTokens();

    if (is_first_in_pipeline && input_redirect != "")
    {   
        readRedirect();

        seperateOnWhitespaces();

        syntaxTokenAnalysis();

        checkRedirectTokens();

        classifyTokens();
    }

    createCommand();
    return final_command;
}

void Parser::checkRedirectTokens()
{
    for (int i = 0; i < cmd_tokens.size(); i++)
    {
        if (cmd_tokens[i]->type() != Arg)
            throw SyntaxException("Input redirect can only contain arguments!");
    }
}




