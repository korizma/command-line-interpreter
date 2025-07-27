#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <vector>
#include <exception>
#include <string>
#include "../config.h"

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

class CommandException : public std::exception
{
    public:
        explicit CommandException(const std::string& command) 
        {
             message = "Invalid command: \'" + command + "\'!";
        }

        virtual const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
};

class SyntaxException : public std::exception
{
    public:
        explicit SyntaxException(const std::string& line, const std::vector<int>& indx_errors) 
        {
            message = "Unexpected characters:\n";

            message += line;
            message += '\n';

            std::string temp = "";
            for (int i = 0; i < line.size(); i++)
                temp += " ";
            
            for (int i = 0; i < indx_errors.size(); i++)
                temp[indx_errors[i]] = '^';
            
            message += temp;
        }

        explicit SyntaxException(TokenType stype)
        {
            if (stype == InRedirect)
            {
                message = "Invalid input redirect position in command!";
            }
            else if (stype == Option)
            {
                message = "Invalid option position in command!";
            }
            else if (stype == OutRedirect)
            {
                message = "Invalid output redirect position in command!";
            }
            else if (stype == Arg)
            {
                message = "Invalid argument position in command!";
            }
        }

        explicit SyntaxException(const std::string& error_msg)
        {
            message = "Something unexpected happened: " + error_msg;
        }

        virtual const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
};

class SemanticFlowException : public std::exception
{
    public:
        explicit SemanticFlowException(const bool& input_flow_error) 
        {
            if (input_flow_error)
                message = "Input flow collision!";
            else
                message = "Ouput flow collision!";
        }

        explicit SemanticFlowException(const std::string& type) 
        {
            message = "No source/destination after: \'" + type + "\'!";
        }

        virtual const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
};

class PipelineException : public std::exception
{
    public:
        explicit PipelineException(const std::string& filename) 
        {
            message = "Input redirect file: \'" + filename + "\', has pipeline arguments!";
        }

        virtual const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
};

#endif 