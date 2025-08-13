#ifndef PROMPTCOMMAND_H
#define PROMPTCOMMAND_H

#include "command.h"

class PromptCommand : public Command 
{
    private:
        void isValid() override;

        std::string getOutput() override;

    public:
        PromptCommand(InputStream* inputStream, OutStream* outputStream, const std::vector<Token*>& options)
            : Command(inputStream, outputStream, options) {}
        ~PromptCommand();

        static std::string getType();

        bool hasOutputStream() const override;
};


#endif // PROMPTCOMMAND_H