
#ifndef COMMANDOUTSTREAM_H
#define COMMANDOUTSTREAM_H

#include "outstream.h"
#include <string>
#include "../InStream/commandinstream.h"

class CommandOutStream : public OutStream 
{

    private:
        CommandInStream _commandInStream;

    public:
        CommandOutStream(CommandInStream& commandInStream);

        void writeStream(const std::string& data) override;
};

inline CommandOutStream::CommandOutStream(CommandInStream& commandInStream)
	: OutStream(OutStreamType::CommandOutStream), _commandInStream(commandInStream) {}

inline void CommandOutStream::writeStream(const std::string& data) 
{
	_commandInStream.writeStream(data);
}

#endif // COMMANDOUTSTREAM_H
