#ifndef WCCOMMAND_H
#define WCCOMMAND_H

#include "command.h"

class WcCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

    public:
        WcCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, Command* next_in_pipeline = NULL)
                : Command(arguments, options, next_in_pipeline) {}
        ~WcCommand();


        static std::string getType();
};


#endif // WCCOMMAND_H