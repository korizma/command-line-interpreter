#include <iostream>
#include "terminal.h"
#include <csignal>
#include "HelperClasses/parser.h"

using namespace std;

int main()
{
    // cout << "Welcome to CLI!" << endl;
    // Terminal::run();
    IOHelper nes;
    string input = nes.getLine(); 
    Parser* temp = new Parser(input);
    temp->parse();
    return 0;
}