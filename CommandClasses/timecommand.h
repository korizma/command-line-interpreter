#ifndef TIMECOMMAND_H
#define TIMECOMMAND_H

#include "command.h"

class TimeCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        TimeCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options)
                : Command(arguments, options) {}
        ~TimeCommand();

        virtual void execute() override;

        static std::string getType();
};


#endif // TIMECOMMAND_H