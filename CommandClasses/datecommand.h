#ifndef DATECOMMAND_H
#define DATECOMMAND_H

#include "command.h"

class DateCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        DateCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, Command* next_in_pipeline = NULL)
                : Command(arguments, options, next_in_pipeline) {}
        ~DateCommand();

        virtual void execute() override;

        static std::string getType();
};


#endif // DATECOMMAND_H