#ifndef DATECOMMAND_H
#define DATECOMMAND_H

#include "command.h"

class DateCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

        virtual void processInput() override;

    public:
        DateCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string &output_redirect, bool is_append)        
                : Command(arguments, options, output_redirect, is_append)  {}
        ~DateCommand();

        static std::string getType();
};


#endif // DATECOMMAND_H