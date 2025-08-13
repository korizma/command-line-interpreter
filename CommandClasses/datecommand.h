#ifndef DATECOMMAND_H
#define DATECOMMAND_H

#include "command.h"

class DateCommand : public Command 
{
    private:
        void isValid() override;

        std::string getOutput() override;

    public:
        DateCommand(InputStream* inputStream, OutStream* outputStream, const std::vector<Token*>& options)
            : Command(inputStream, outputStream, options) {}
        ~DateCommand();

        static std::string getType();
};


#endif // DATECOMMAND_H