#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H

#include "command.h"

class ExitCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        ExitCommand(const std::string& original_command, const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string& in_filename, const std::string& out_filename)
                : Command(original_command, arguments, options, in_filename, out_filename) {}
        ~ExitCommand();

        virtual void execute() override;

        static std::string getType();
};


#endif // EXITCOMMAND_H