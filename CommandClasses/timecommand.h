#ifndef TIMECOMMAND_H
#define TIMECOMMAND_H

#include "command.h"

class TimeCommand : public Command 
{
    private:
        void isValid() override;

        std::string getOutput() override;

    public:
        TimeCommand(InputStream* inputStream, OutStream* outputStream, const std::vector<Token*>& options)
            : Command(inputStream, outputStream, options) {}
        ~TimeCommand();

        static std::string getType();
};


#endif // TIMECOMMAND_H