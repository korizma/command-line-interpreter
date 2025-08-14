#include "commandoutstream.h"

CommandOutStream::CommandOutStream(CommandInStream* commandInStream)
	: OutStream(OutStreamType::CommandOutStream), _commandInStream(commandInStream) {}

void CommandOutStream::writeStream(const std::string& data) 
{
	_commandInStream->writeStream(data);
}

void CommandOutStream::print() const
{
    std::cout << "Command Out Stream: " << std::endl;
    _commandInStream->print();
}
