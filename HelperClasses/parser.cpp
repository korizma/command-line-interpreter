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

Command* Parser::parse()
{
    seperateOnWhitespaces();
    tokenize();
    return NULL;

    classifyTokens();

    if (input_redirect != "")
    {
        readRedirect();
        seperateOnWhitespaces();
        tokenize();
    }

    if (is_pipeline_cmd)
    {
        return parsePipelineCmd();
    }

    createCommand();
    return final_command;
}

Parser::Parser(std::string &line)
{
    original_line = line;
    is_pipeline_cmd = has_regular_args = false;
    input_redirect = output_redirect = "";
}

void Parser::seperateOnWhitespaces()
{
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
                curr_str = "";
            }
            tokens.push_back("|");
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
        tokens.push_back(curr_str);
}


void Parser::tokenize()
{
    if (tokens.size() == 0)
        return;
    
    if (command_name == "")
    {   
        command_name = tokens[0];
        tokens.erase(tokens.begin());
    }

    for (int i = 0; i < tokens.size(); i++)
    {
        if ((tokens[i] == "<" || tokens[i] == "<<" || tokens[i] == ">") && i + 1 < tokens.size())
        {
            tokens[i] += tokens[i+1];
            tokens.erase(tokens.begin() + i + 1);
        }
    }
}








