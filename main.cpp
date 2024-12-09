#include <iostream>
#include "terminal.h"
#include "HelperClasses/parser.h"
#include "HelperClasses/iohandler.h"
#include "CommandClasses/command.h"
#include <csignal>

using namespace std;


void handleSignal(int signal) {
    if (signal == SIGTSTP) {
        std::cout << "\nCtrl+D caught. Ignoring signal!" << std::endl;
    }
    if (signal == SIGSEGV)
    {
        std::cout << "\n oops!" << std::endl;
        exit(0);
    }
}

int main()
{
    signal(SIGINT, handleSignal);
    signal(SIGTSTP, handleSignal);
    signal(SIGSEGV, handleSignal);

    cout << "Welcome to CLI!" << endl;
    Terminal::run();
    // string a = IOHandler::getInput();
    // string b = IOHandler::getLine();
    // cout << "Input: " << a << endl;
    // cout << "Line: " << b << endl;
    return 0;
}