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
        HeadCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, Command* next_in_pipeline = NULL)
                : Command(arguments, options, next_in_pipeline) {}
        ~HeadCommand();

        static std::string getType();
};
#endif // HEADCOMMAND_H