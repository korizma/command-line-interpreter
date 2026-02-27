#ifndef RMCOMMAND_H
#define RMCOMMAND_H

#include "command.hpp"

class RmCommand : public Command 
{
    private:
        void isValid() override;

        std::string getOutput() override;

    public:
        RmCommand(InputStream* inputStream, OutStream* outputStream, const std::vector<Token*>& options)
            : Command(inputStream, outputStream, options) {}
        ~RmCommand();

        static std::string getType();

        virtual bool hasOutputStream() const override;
};


#endif // RMCOMMAND_H