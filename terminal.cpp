#include "terminal.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include "CommandClasses/command.h"
#include "HelperClasses/parser.h"
#include "HelperClasses/iohandler.h"


Terminal::Terminal()
{
    char buffer[500];
    ::getcwd(buffer, sizeof(buffer));
    std::string current_dir(buffer);
    path = current_dir;
    ready_sign = "$";
}

Terminal* Terminal::getInstance()
{
    static Terminal instance;
    return &instance;
}

std::string Terminal::getPath()
{
    return path;
}

void Terminal::run()
{
    Terminal *term = getInstance();
    term->start();
}

void Terminal::start()
{
    std::string line;
    Command *curr_command;

    while (true)
    {
        std::cout << ready_sign;
        line = IOHandler::getLine();
        curr_command = Parser::parse(line);
        curr_command->execute();
        delete curr_command;
    }
}


void Terminal::changeSign(std::string new_sign)
{
    ready_sign = new_sign;
}


