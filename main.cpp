#include <iostream>
#include "terminal.hpp"
#include <csignal>

using namespace std;

int main()
{
    cout << "Welcome to CLI!" << endl;
    Terminal::run();

    return 0;
}