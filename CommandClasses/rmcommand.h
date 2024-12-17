#ifndef RMCOMMAND_H
#define RMCOMMAND_H

#include "command.h"

class RmCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        RmCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options)
                : Command(arguments, options) {}
        ~RmCommand();

        virtual void execute() override;

        static std::string getType();
};


#endif // RMCOMMAND_H