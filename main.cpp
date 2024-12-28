#include <iostream>
#include "terminal.h"
#include "HelperClasses/parser.h"
#include "HelperClasses/iohandler.h"
#include "CommandClasses/command.h"
#include <csignal>

using namespace std;

int main()
{
    cout << "Welcome to CLI!" << endl;
    // Terminal::testProgram();
    Terminal::run();
    return 0;
}