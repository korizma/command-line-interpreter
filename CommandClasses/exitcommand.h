#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H

#include "command.h"

class ExitCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

        virtual void processInput() override;

    public:
        ExitCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string &output_redirect, bool is_append)        
                : Command(arguments, options, output_redirect, is_append)  {}
        ~ExitCommand();

        static std::string getType();
};


#endif // EXITCOMMAND_H