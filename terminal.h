#ifndef TERMINAL_H
#define TERMINAL_H
#include <string>

class Terminal 
{
    private:
        std::string ready_sign;
        std::string path;

        Terminal();
        void start();
    
    public:

        static void run();
        std::string getPath();
        static Terminal* getInstance();

};



#endif // TERMINAL_H