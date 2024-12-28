#ifndef RMCOMMAND_H
#define RMCOMMAND_H

#include "command.h"

class RmCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

    public:
        RmCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, Command* next_in_pipeline = NULL)
                : Command(arguments, options, next_in_pipeline) {}
        ~RmCommand();

        static std::string getType();
};


#endif // RMCOMMAND_H