#ifndef PROMPTCOMMAND_H
#define PROMPTCOMMAND_H

#include "command.h"

class PromptCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        PromptCommand(const std::string& original_command, const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string& in_filename, const std::string& out_filename)
                : Command(original_command, arguments, options, in_filename, out_filename) {}
        ~PromptCommand();

        virtual void execute() override;

        static std::string getType();
};


#endif // PROMPTCOMMAND_H