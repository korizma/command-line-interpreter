#ifndef ECHOCOMMAND_H
#define ECHOCOMMAND_H

#include "command.h"

class EchoCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

    public:
        EchoCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string &output_redirect, bool is_append)        
                : Command(arguments, options, output_redirect, is_append)  {}
        ~EchoCommand();

        static std::string getType();
};


#endif // ECHOCOMMAND_H