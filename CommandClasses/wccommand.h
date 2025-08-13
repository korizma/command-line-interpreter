#ifndef WCCOMMAND_H
#define WCCOMMAND_H

#include "command.h"

class WcCommand : public Command 
{
    private:
        void isValid() override;

        std::string getOutput() override;

        bool needsInput() const override;

        bool acceptsFileArgRead() const override;

    public:
        WcCommand(InputStream* inputStream, OutStream* outputStream, const std::vector<Token*>& options)
            : Command(inputStream, outputStream, options) {}
        ~WcCommand();


        static std::string getType();
};


#endif // WCCOMMAND_H