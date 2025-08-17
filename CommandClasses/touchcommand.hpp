#ifndef TOUCHCOMMAND_H
#define TOUCHCOMMAND_H

#include "command.hpp"

class TouchCommand : public Command 
{
    private:
        virtual void isValid() override;

        virtual std::string getOutput() override;

    public:
        TouchCommand(InputStream* inputStream, OutStream* outputStream, const std::vector<Token*>& options)
            : Command(inputStream, outputStream, options) {}
        ~TouchCommand();

        static std::string getType();

        virtual bool hasOutputStream() const override;
};


#endif // TOUCHCOMMAND_H