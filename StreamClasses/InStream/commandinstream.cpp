#include "commandinstream.h"

CommandInStream::CommandInStream()
	: InputStream(InputStreamType::CommandInStream) {}

std::vector<Token*> CommandInStream::readStream() 
{
	return _command_args;
}

void CommandInStream::writeStream(const std::string& data) 
{
    _command_args.push_back(new ArgumentToken("\"" + data + "\"", 0));
}

void CommandInStream::print() const
{
    std::cout << "Command In Stream: " << std::endl;
    for (const auto& token : _command_args)
    {
        token->print();
    }
}