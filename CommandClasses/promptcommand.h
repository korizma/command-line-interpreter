#ifndef PROMPTCOMMAND_H
#define PROMPTCOMMAND_H

#include "command.h"

class PromptCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

        virtual void processInput() override;

    public:
        PromptCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, Command* next_in_pipeline = NULL)
                : Command(arguments, options, next_in_pipeline) {}
        ~PromptCommand();

        static std::string getType();
};


#endif // PROMPTCOMMAND_H