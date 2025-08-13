#ifndef BATCHCOMMAND_H
#define BATCHCOMMAND_H

#include <vector>
#include <memory>
#include "command.h"
// this is not final TODO logic
class BatchCommand : public Command 
{
    private:
        bool nested_call;

        void isValid() override;
        std::string getOutput() override;

    protected:
        void setToNested();
        void acceptNestedArg(std::string &commands);

    public:
        BatchCommand(InputStream* inputStream, OutStream* outputStream, const std::vector<Token*>& args, const std::vector<Token*>& options);
        ~BatchCommand();

        static std::string getType();
};

#endif // BATCHCOMMAND_H