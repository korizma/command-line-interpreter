#ifndef TRUNICATECOMMAND_H
#define TRUNICATECOMMAND_H

#include "command.h"

class TrunicateCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        TrunicateCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options)
                : Command(arguments, options) {}
        ~TrunicateCommand();

        virtual void execute() override;

        static std::string getType();
};


#endif // TRUNICATECOMMAND_H