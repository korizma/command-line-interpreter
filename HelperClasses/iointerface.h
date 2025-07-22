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

inline std::string IOInterface::readFile(const std::string &filename) { return ""; }

inline void IOInterface::writeFile(const std::string &filename, const std::string &content) {}

inline void IOInterface::createFile(const std::string &filename) {}

inline std::string IOInterface::getInput() { return ""; }

inline std::string IOInterface::getLine() { return ""; }

inline void IOInterface::appendFile(const std::string& filename, const std::string& content) {}

inline void IOInterface::clearFile(const std::string& filename) {}

inline void IOInterface::deleteFile(const std::string& filename) {}

#endif