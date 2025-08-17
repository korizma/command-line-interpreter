#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H

#include "command.hpp"

class ExitCommand : public Command 
{
    private:
        void isValid() override;

        std::string getOutput() override;

    public:
        ExitCommand(InputStream* inputStream, OutStream* outputStream, const std::vector<Token*>& options)
            : Command(inputStream, outputStream, options) {}
        ~ExitCommand();

        static std::string getType();

        bool hasOutputStream() const override;
};


#endif // EXITCOMMAND_H