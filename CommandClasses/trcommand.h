#ifndef TRCOMMAND_H
#define TRCOMMAND_H

#include <string>
#include "command.h"

class TrCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

    public:
        TrCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, Command* next_in_pipeline = NULL)
                : Command(arguments, options, next_in_pipeline) {}
        ~TrCommand();


        static std::string getType();
};

#endif // TRCOMMAND_H