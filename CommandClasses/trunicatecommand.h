#ifndef TRUNICATECOMMAND_H
#define TRUNICATECOMMAND_H

#include "command.h"

class TrunicateCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        TrunicateCommand(const std::string& original_command, const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string& in_filename, const std::string& out_filename)
                : Command(original_command, arguments, options, in_filename, out_filename) {}
        ~TrunicateCommand();

        virtual void execute() override;

        static std::string getType();
};


#endif // TRUNICATECOMMAND_H