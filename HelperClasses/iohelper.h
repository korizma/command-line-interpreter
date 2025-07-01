#ifndef IOHELPER_H
#define IOHELPER_H
#include <string>
#include <fstream>
#include "../ExceptionClasses/exception.h"
#include "iointerface.h"

class IOHelper: public IOInterface
{
    public:
        std::string readFile(const std::string &filename) override;

        void writeFile(const std::string &filename, const std::string &content) override;

        void createFile(const std::string& filename) override;

        std::string getInput() override;

        std::string getLine() override;

        void appendFile(const std::string& filename, const std::string& content) override;

        void clearFile(const std::string& filename) override;

        void deleteFile(const std::string& filename) override;
};

#endif // IOHELPER_H