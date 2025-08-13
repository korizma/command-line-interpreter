#ifndef TRCOMMAND_H
#define TRCOMMAND_H

#include <string>
#include "command.h"

class TrCommand : public Command 
{
    private:
        void isValid() override;

        std::string getOutput() override;

        bool needsInput() const override;

        bool acceptsFileArgRead() const override;

    public:
        TrCommand(InputStream* inputStream, OutStream* outputStream, const std::vector<Token*>& options)
            : Command(inputStream, outputStream, options) {}
        ~TrCommand();


        static std::string getType();
};

#endif // TRCOMMAND_H