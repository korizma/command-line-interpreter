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
    semanticTokenAnalysis();
    syntaxTokenAnalysis();
    classifyTokens();
    print();
    return NULL;

    if (input_redirect != "")
    {
        readRedirect();
        seperateOnWhitespaces();
        semanticFlowAnalysis();
    }

    if (is_pipeline_cmd)
    {
        return parsePipelineCmd();
    }


    classifyTokens();

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
        if (curr_ch == '\t')
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

    if (has_args && has_input_redirect)
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

    // for (const auto& token : cmd_tokens)
    //     token->print();
}






