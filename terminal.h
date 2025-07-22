#ifndef TERMINAL_H
#define TERMINAL_H
#include <string>
#include "HelperClasses/iohelper.h"

class Terminal 
{
    private:
        std::string ready_sign;
        std::string path;

        IOInterface io;

        Terminal();
        void start();
    
    public:

        static void run();
        std::string getPath();
        static Terminal* getInstance();
        void changeSign(std::string new_sign);
        static void testProgram();

};



#endif // TERMINAL_H