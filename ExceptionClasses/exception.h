#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class ArgumentException : public std::exception {
public:
    explicit ArgumentException(const int& num_args_expected, const int& num_args_recieved) 
    {        
        if (num_args_expected < num_args_recieved)
            message = "Too many arguments!";
        else
            message = "Not enough arguments!";
        message += " Recieved: " + std::to_string(num_args_recieved) + ", Expected: " + std::to_string(num_args_expected);
    }

    explicit ArgumentException(const bool& expected_file)
    {
        if (expected_file)
            message = "Invalid format! File expected!";
        else
            message = "Invalid format! Text expected!";
    }

    virtual const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};

class OptionException : public std::exception {
public:
    explicit OptionException(const int& num_opts_expected, const int& num_opts_recieved, const bool& valid_options = true) 
    {
        if (!valid_options)
            message = "Invalid option(s)!";
        else
        {
            if (num_opts_expected < num_opts_recieved)
                message = "Too many options!";
            else
                message = "Not enough options!";
            message += " Recieved: " + std::to_string(num_opts_recieved) + ", Expected: " + std::to_string(num_opts_expected);
        }
    }

    explicit OptionException(const std::string& invalid_option)
    {
        message = "Invalid option: \'" + invalid_option + "\'!";
    }

    virtual const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};

class FileException : public std::exception {
public:
    explicit FileException(const std::string& file, const bool& file_exists) 
    {
        if (file_exists)
            message = "File \'" + file + "\' already exsists!";  
        else
            message = "File \'" + file + "\' doesn't exsists!";  
    }

    explicit FileException(const std::string& file): message("Something went wrong! Problem: \'" + file + "\'") {}

    virtual const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};

#endif 