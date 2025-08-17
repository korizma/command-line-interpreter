#include "iohelper.hpp"
#include <string>
#include <fstream>
#include "../terminal.hpp"
#include "../ExceptionClasses/exception.hpp"
#include <iostream>
#include <limits>

std::string IOHelper::readFile(const std::string &filename) 
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

void IOHelper::writeFile(const std::string &filename, const std::string &content) 
{
    std::string full_path = Terminal::getInstance()->getPath() + "/" + filename;
    std::ofstream file(full_path);
    if (!file.is_open()) 
    {
        throw FileException("what!");
    }
    file << content;
    file.close();
}

void IOHelper::createFile(const std::string &filename) 
{
    std::string full_path = Terminal::getInstance()->getPath() + "/" + filename;

    std::ifstream check_if_exists(full_path);
    if (check_if_exists.is_open())
    {
        check_if_exists.close();
        throw FileException("this file exists!");
    }

    std::ofstream file(full_path);
    if (!file.is_open()) 
    {
        throw FileException("what!");
    }
    file.close();
}

std::string IOHelper::getInput() 
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

std::string IOHelper::getLine() 
{
    std::string line;
    std::getline(std::cin, line);
    return line;
}

void IOHelper::appendFile(const std::string& filename, const std::string& content)
{
    std::string full_path = Terminal::getInstance()->getPath() + "/" + filename;
    std::ofstream file(full_path, std::ios::app);
    if (!file.is_open()) 
    {
        throw FileException(filename);
    }
    file << content;
    file.close();
}

void IOHelper::clearFile(const std::string& filename)
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

void IOHelper::deleteFile(const std::string& filename)
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

