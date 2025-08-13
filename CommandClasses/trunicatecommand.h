#ifndef TRUNICATECOMMAND_H
#define TRUNICATECOMMAND_H

#include "command.h"

class TrunicateCommand : public Command 
{
    private:
        void isValid() override;

        std::string getOutput() override;

    public:
        TrunicateCommand(InputStream* inputStream, OutStream* outputStream, const std::vector<Token*>& options)
            : Command(inputStream, outputStream, options) {}
        ~TrunicateCommand();


        static std::string getType();

        virtual bool hasOutputStream() const override;
};


#endif // TRUNICATECOMMAND_H