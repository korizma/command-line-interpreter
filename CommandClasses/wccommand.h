#ifndef WCCOMMAND_H
#define WCCOMMAND_H

#include "command.h"

class WcCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        WcCommand(const std::string& original_command, const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string& in_filename, const std::string& out_filename)
                : Command(original_command, arguments, options, in_filename, out_filename) {}
        ~WcCommand();

        virtual void execute() override;

        static std::string getType();
};


#endif // WCCOMMAND_H