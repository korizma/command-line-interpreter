#ifndef TOUCHCOMMAND_H
#define TOUCHCOMMAND_H

#include "command.h"

class TouchCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        TouchCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options)
                : Command(arguments, options) {}
        ~TouchCommand();

        virtual void execute() override;

        static std::string getType();
};


#endif // TOUCHCOMMAND_H