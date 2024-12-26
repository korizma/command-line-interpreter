#ifndef BATCHCOMMAND_H
#define BATCHCOMMAND_H

#include <vector>
#include <memory>
#include "command.h"

class BatchCommand : public Command 
{
    private:
        virtual void isValid() override;

    public:
        BatchCommand(const std::vector<std::string>& arguments, const std::vector<std::string>& options, Command* next_in_pipeline = NULL)
                : Command(arguments, options, next_in_pipeline) {}
        ~BatchCommand();

        virtual void execute() override;

        static std::string getType();
};

#endif // BATCHCOMMAND_H