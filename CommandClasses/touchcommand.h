#ifndef TOUCHCOMMAND_H
#define TOUCHCOMMAND_H

#include "command.h"

class TouchCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

        virtual void processInput() override;

    public:
        TouchCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string &output_redirect, bool is_append)        
                : Command(arguments, options, output_redirect, is_append)  {}
        ~TouchCommand();

        static std::string getType();
};


#endif // TOUCHCOMMAND_H