#ifndef PROMPTCOMMAND_H
#define PROMPTCOMMAND_H

#include "command.h"

class PromptCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        PromptCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, Command* next_in_pipeline = NULL)
                : Command(arguments, options, next_in_pipeline) {}
        ~PromptCommand();

        virtual void execute() override;

        static std::string getType();
};


#endif // PROMPTCOMMAND_H