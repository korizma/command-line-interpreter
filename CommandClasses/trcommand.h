#ifndef TRCOMMAND_H
#define TRCOMMAND_H

#include <string>
#include "command.h"

class TrCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

        virtual void processInput() override;

    public:
        TrCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string &output_redirect, bool is_append)        
                : Command(arguments, options, output_redirect, is_append)  {}
        ~TrCommand();


        static std::string getType();
};

#endif // TRCOMMAND_H