
#ifndef COMMANDOUTSTREAM_H
#define COMMANDOUTSTREAM_H

#include "outstream.h"
#include <string>
#include "../InStream/commandinstream.h"

class CommandOutStream : public OutStream 
{

    private:
        CommandInStream* _commandInStream;

    public:
        CommandOutStream(CommandInStream* commandInStream);

        void writeStream(const std::string& data) override;

        void print() const override;

};


#endif // COMMANDOUTSTREAM_H
