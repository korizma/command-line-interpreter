#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H

#include "command.h"

class ExitCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

        virtual void processInput() override;

    public:
        ExitCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, Command* next_in_pipeline = NULL)
                : Command(arguments, options, next_in_pipeline) {}
        ~ExitCommand();

        static std::string getType();
};


#endif // EXITCOMMAND_H