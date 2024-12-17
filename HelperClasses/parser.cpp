#include <iostream>
#include <string>
#include <vector>

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

Command* Parser::parse(std::string input)
{ 
    std::vector<std::string> divided;

    std::string curr = "";
    int i = 0;
    bool small_q = false, big_q = false;
    while (i <= input.size())
    {
        if (((input[i] == ' ' || input[i] == '\t') && !(big_q || small_q)) || i == input.size())
        {
            divided.push_back(curr);
            curr = "";
            i++;
            continue;
        }
        if (input[i] == '\'' && !big_q)
            small_q = !small_q;

        if (input[i] == '\"' && !small_q)
            big_q = !big_q;

        curr += input[i];
        i++;
    }
    if (divided.size() == 0)
        return NULL;
        

    std::vector<std::string> arguments, options;
    std::string command_type = divided[0];

    for (int i = 1; i < divided.size(); i++)
    {
        if (divided[i] == "")
            continue;
        
        if (divided[i][0] == '-')
            options.push_back(divided[i]);
        else
        {
            arguments.push_back(divided[i]);
        }
    }

    Command* komanda = Parser::createCommand(command_type, input, arguments, options, "", "");

    return komanda;
}

Command* Parser::createCommand(const std::string& cmd_name, std::string original_command, const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string& in, const std::string& out)
{
    if (cmd_name == EchoCommand::getType())
    {
        return new EchoCommand(original_command, arguments, options, in, out);
    }
    if (cmd_name == TimeCommand::getType())
    {
        return new TimeCommand(original_command, arguments, options, in, out);
    }
    if (cmd_name == DateCommand::getType())
    {
        return new DateCommand(original_command, arguments, options, in, out);
    }
    if (cmd_name == TouchCommand::getType())
    {
        return new TouchCommand(original_command, arguments, options, in, out);
    }
    if (cmd_name == WcCommand::getType())
    {
        return new WcCommand(original_command, arguments, options, in, out);
    }
    if (cmd_name == ExitCommand::getType())
    {
        return new ExitCommand(original_command, arguments, options, in, out);
    }
    if (cmd_name == HeadCommand::getType())
    {
        return new HeadCommand(original_command, arguments, options, in, out);
    }
    if (cmd_name == PromptCommand::getType())
    {
        return new PromptCommand(original_command, arguments, options, in, out);
    }
    if (cmd_name == RmCommand::getType())
    {
        return new RmCommand(original_command, arguments, options, in, out);
    }
    if (cmd_name == TrCommand::getType())
    {
        return new TrCommand(original_command, arguments, options, in, out);
    }
    if (cmd_name == TrunicateCommand::getType())
    {
        return new TrunicateCommand(original_command, arguments, options, in, out);
    }
    if (cmd_name == BatchCommand::getType())
    {
        return new BatchCommand(original_command, arguments, options, in, out);
    }

    return NULL;
}
        