#ifndef TOUCHCOMMAND_H
#define TOUCHCOMMAND_H

#include "command.h"

class TouchCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

        virtual void processInput() override;

    public:
        TouchCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, Command* next_in_pipeline = NULL)
                : Command(arguments, options, next_in_pipeline) {}
        ~TouchCommand();

        static std::string getType();
};


#endif // TOUCHCOMMAND_H