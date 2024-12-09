#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class ArgumentException : public std::exception {
public:
    explicit ArgumentException(const std::string& message) : message(message) {}

    virtual const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};

class OptionException : public std::exception {
public:
    explicit OptionException(const std::string& message) : message(message) {}

    virtual const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};

class FileException : public std::exception {
public:
    explicit FileException(const std::string& message) : message(message) {}

    virtual const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};

#endif 