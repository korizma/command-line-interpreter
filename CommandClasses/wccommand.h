#ifndef WCCOMMAND_H
#define WCCOMMAND_H

#include "command.h"

class WcCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        WcCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options)
                : Command(arguments, options) {}
        ~WcCommand();

        virtual void execute() override;

        static std::string getType();
};


#endif // WCCOMMAND_H