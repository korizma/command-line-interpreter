#ifndef TRUNICATECOMMAND_H
#define TRUNICATECOMMAND_H

#include "command.h"

class TrunicateCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

        virtual void processInput() override;

    public:
        TrunicateCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, Command* next_in_pipeline = NULL)
                : Command(arguments, options, next_in_pipeline) {}
        ~TrunicateCommand();


        static std::string getType();
};


#endif // TRUNICATECOMMAND_H