#ifndef HEADCOMMAND_H
#define HEADCOMMAND_H

#include "command.hpp"
#include <iostream>
#include <string>


class HeadCommand : public Command 
{
    private:
        void isValid() override;

        std::string getOutput() override;

        bool needsInput() const override;

        bool acceptsFileArgRead() const override;

    public:
        HeadCommand(InputStream* inputStream, OutStream* outputStream, const std::vector<Token*>& options)
            : Command(inputStream, outputStream, options) {}
        ~HeadCommand();

        static std::string getType();
};
#endif // HEADCOMMAND_H