#ifndef ECHOCOMMAND_H
#define ECHOCOMMAND_H

#include "command.h"

class EchoCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        EchoCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options)
                : Command(arguments, options) {}
        ~EchoCommand();

        virtual void execute() override;

        static std::string getType();
};


#endif // ECHOCOMMAND_H