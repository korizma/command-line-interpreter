#ifndef TIMECOMMAND_H
#define TIMECOMMAND_H

#include "command.h"

class TimeCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        TimeCommand(const std::string& original_command, const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string& in_filename, const std::string& out_filename)
                : Command(original_command, arguments, options, in_filename, out_filename) {}
        ~TimeCommand();

        virtual void execute() override;

        static std::string getType();
};


#endif // TIMECOMMAND_H