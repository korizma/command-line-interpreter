#ifndef DATECOMMAND_H
#define DATECOMMAND_H

#include "command.h"

class DateCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        DateCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options)
                : Command(arguments, options) {}
        ~DateCommand();

        virtual void execute() override;

        static std::string getType();
};


#endif // DATECOMMAND_H