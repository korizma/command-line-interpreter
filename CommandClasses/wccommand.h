#ifndef WCCOMMAND_H
#define WCCOMMAND_H

#include "command.h"

class WcCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

    public:
        WcCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string &output_redirect, bool is_append)        
                : Command(arguments, options, output_redirect, is_append)  {}
        ~WcCommand();


        static std::string getType();
};


#endif // WCCOMMAND_H