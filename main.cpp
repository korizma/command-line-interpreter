#include <iostream>
#include "terminal.h"
#include "HelperClasses/parser.h"
#include "HelperClasses/iohandler.h"
#include "CommandClasses/command.h"
#include <csignal>
#include "HelperClasses/iohelper.h"


using namespace std;


// void handleSignal(int signal) {
//     if (signal == SIGTSTP) {
//         std::cout << "\nCtrl+D caught. Ignoring signal!" << std::endl;
//     }
//     if (signal == SIGSEGV)
//     {
//         std::cout << "\n oops!" << std::endl;
//         exit(0);
//     }
// }

void testNew()
{
    IOHelper ioHelper;
    try {
        ioHelper.createFile("test.txt");
        ioHelper.writeFile("test.txt", "Hello, World!");
        string content = ioHelper.readFile("test.txt");
        cout << "File content: " << content << endl;
        ioHelper.createFile("test.txt");
    } catch (const FileException &e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main()
{
    testNew();
    // signal(SIGINT, handleSignal);
    // signal(SIGTSTP, handleSignal);
    // signal(SIGSEGV, handleSignal);

    // cout << "Welcome to CLI!" << endl;
    // Terminal::run();
    // string a = IOHandler::getInput();
    // string b = IOHandler::getLine();
    // cout << "Input: " << a << endl;
    // cout << "Line: " << b << endl;
    return 0;
}