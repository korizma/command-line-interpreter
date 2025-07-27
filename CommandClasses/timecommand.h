#ifndef TIMECOMMAND_H
#define TIMECOMMAND_H

#include "command.h"

class TimeCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

        virtual void processInput() override;

    public:
        TimeCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string &output_redirect, bool is_append)        
                : Command(arguments, options, output_redirect, is_append)  {}
        ~TimeCommand();

        static std::string getType();
};


#endif // TIMECOMMAND_H