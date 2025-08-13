#ifndef ECHOCOMMAND_H
#define ECHOCOMMAND_H

#include "command.h"

class EchoCommand : public Command 
{
    private:
        void isValid() override;

        std::string getOutput() override;

        bool needsInput() const override;

        bool acceptsFileArgRead() const override;

    public:
        EchoCommand(InputStream* inputStream, OutStream* outputStream, const std::vector<Token*>& options)
            : Command(inputStream, outputStream, options) {}
        ~EchoCommand();

        static std::string getType();
};


#endif // ECHOCOMMAND_H