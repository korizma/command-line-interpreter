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
        TrunicateCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string &output_redirect, bool is_append)        
                : Command(arguments, options, output_redirect, is_append)  {}
        ~TrunicateCommand();


        static std::string getType();
};


#endif // TRUNICATECOMMAND_H