#ifndef IOINTERFACE_H
#define IOINTERFACE_H
#include <string>

/*
    * read file
    * create file
    * get input ~ input until CTRL D
    * get line ~ input until \n
*/

class IOInterface
{
    public:
        virtual std::string readFile(const std::string &filename) = 0;

        virtual void writeFile(const std::string &filename, const std::string &content) = 0;

        virtual void createFile(const std::string& filename) = 0;

        // gets extra input if command requires
        virtual std::string getInput() = 0;

        // gets next line (command)
        virtual std::string getLine() = 0;

        virtual void appendFile(const std::string& filename, const std::string& content) = 0;

        virtual void clearFile(const std::string& filename) = 0;

        virtual void deleteFile(const std::string& filename) = 0;

};

#endif