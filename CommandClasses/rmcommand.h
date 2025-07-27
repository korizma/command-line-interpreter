#ifndef RMCOMMAND_H
#define RMCOMMAND_H

#include "command.h"

class RmCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

        virtual void processInput() override;

    public:
        RmCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string &output_redirect, bool is_append)        
                : Command(arguments, options, output_redirect, is_append)  {}
        ~RmCommand();

        static std::string getType();
};


#endif // RMCOMMAND_H