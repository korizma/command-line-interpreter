#ifndef HEADCOMMAND_H
#define HEADCOMMAND_H

#include "command.h"
#include <iostream>
#include <string>


class HeadCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

    public:
        HeadCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string &output_redirect, bool is_append)        
                : Command(arguments, options, output_redirect, is_append)  {}
        ~HeadCommand();

        static std::string getType();
};
#endif // HEADCOMMAND_H