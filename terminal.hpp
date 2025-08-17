#ifndef TERMINAL_H
#define TERMINAL_H
#include <string>
#include "HelperClasses/iohelper.hpp"

class Terminal 
{
    private:
        std::string ready_sign;
        std::string path;

        IOHelper io;

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