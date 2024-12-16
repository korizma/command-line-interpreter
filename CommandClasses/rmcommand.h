#ifndef RMCOMMAND_H
#define RMCOMMAND_H

#include "command.h"

class RmCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        RmCommand(const std::string& original_command, const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string& in_filename, const std::string& out_filename)
                : Command(original_command, arguments, options, in_filename, out_filename) {}
        ~RmCommand();

        virtual void execute() override;

        static std::string getType();
};


#endif // RMCOMMAND_H