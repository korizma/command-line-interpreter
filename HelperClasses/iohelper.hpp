#ifndef IOHELPER_H
#define IOHELPER_H
#include <string>
#include <fstream>
#include "../ExceptionClasses/exception.hpp"

class IOHelper
{
    public:
        virtual std::string readFile(const std::string &filename);

        virtual void writeFile(const std::string &filename, const std::string &content);

        virtual void createFile(const std::string& filename);

        // gets extra input if command requires
        virtual std::string getInput();

        // gets next line (command)
        virtual std::string getLine();

        virtual void appendFile(const std::string& filename, const std::string& content);

        virtual void clearFile(const std::string& filename);

        virtual void deleteFile(const std::string& filename);
};

#endif // IOHELPER_H