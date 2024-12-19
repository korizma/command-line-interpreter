#ifndef IOHANDLER_H
#define IOHANDLER_H
#include <string>
#include <fstream>
#include "../terminal.h"
#include "../ExceptionClasses/exception.h"
#include <limits>
#include <iostream>

class IOHandler 
{
    public:
        static std::string readFile(const std::string& filename);

        static void writeFile(const std::string& filename, const std::string& content);

        static void createFile(const std::string& filename);

        static void clearFile(const std::string& filename);
        
        static void deleteFile(const std::string& filename);

        static std::string getInput();

        static std::string getLine();

};

inline std::string IOHandler::readFile(const std::string& filename)
{
    std::string full_path = Terminal::getInstance()->getPath() + "/" + filename;
    std::ifstream file(full_path);

    if (!file.is_open()) 
    {
        throw FileException(filename, false);
    }
    std::string content;
    std::string line;
    while (std::getline(file, line)) 
    {
        content += line + "\n";
    }
    file.close();
    return content;
}

inline void IOHandler::writeFile(const std::string& filename, const std::string& content)
{
    std::string full_path = Terminal::getInstance()->getPath() + "/" + filename;
    std::ofstream file(full_path);
    if (!file.is_open()) 
    {
        throw FileException(filename);
    }
    file << content;
    file.close();
}

inline std::string IOHandler::getInput()
{
    char c;
    std::string input;
    while ((c = getchar()) != EOF)
        input += c;
    std::cin.clear();
    //for linux use
    std::freopen("/dev/tty", "r", stdin);       
    // for windows use 
    // std::freopen("CON", "r", stdin); 
    return input;
}

inline std::string IOHandler::getLine()
{
    std::string line;
    getline(std::cin, line);
    return line;
}

inline void IOHandler::createFile(const std::string& filename)
{
    std::string full_path = Terminal::getInstance()->getPath() + "/" + filename;

    std::ifstream check_if_exists(full_path);
    if (check_if_exists.is_open())
    {
        check_if_exists.close();
        throw FileException(filename, true);
    }

    std::ofstream file(full_path);
    if (!file.is_open()) 
    {
        throw FileException(filename);
    }
    file.close();
}
    
inline void IOHandler::clearFile(const std::string& filename)
{
    std::string full_path = Terminal::getInstance()->getPath() + "/" + filename;

    std::ifstream check_if_exists(full_path);
    if (!check_if_exists.is_open())
    {
        throw FileException(filename, true);
    }

    std::ofstream file(full_path);
    if (!file.is_open()) 
    {
        throw FileException(filename);
    }
    file << "";
    file.close();
}

inline void IOHandler::deleteFile(const std::string& filename)
{
    std::string full_path = Terminal::getInstance()->getPath() + "/" + filename;
    std::ifstream file(full_path);

    if (!file.is_open()) 
    {
        throw FileException(filename, false);
    }
    file.close();

    if (std::remove(full_path.c_str()))
    {
        throw FileException(filename);
    }
}


#endif // FILEHANDLER_H
