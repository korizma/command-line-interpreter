#ifndef PROMPTCOMMAND_H
#define PROMPTCOMMAND_H

#include "command.h"

class PromptCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        PromptCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options)
                : Command(arguments, options) {}
        ~PromptCommand();

        virtual void execute() override;

        static std::string getType();
};


#endif // PROMPTCOMMAND_H