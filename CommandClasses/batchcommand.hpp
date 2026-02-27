#ifndef BATCHCOMMAND_H
#define BATCHCOMMAND_H

#include <vector>
#include <memory>
#include "command.hpp"
// this is not final TODO logic
class BatchCommand : public Command 
{
    private:
        bool _nested_call;
        bool _input_can_be_overridden;

        void isValid() override;
        std::string getOutput() override;

    protected:
        void setToNested();

        bool inputCanBeOverridden() const;

    public:
        BatchCommand(InputStream* inputStream, OutStream* outputStream, const std::vector<Token*>& options);
        ~BatchCommand();

        static std::string getType();

        bool needsInput() const override;

        bool acceptsFileArgRead() const override;
};

#endif // BATCHCOMMAND_H