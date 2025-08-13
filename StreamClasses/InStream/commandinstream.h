
#ifndef COMMANDINSTREAM_H
#define COMMANDINSTREAM_H

#include "inputstream.h"
#include <vector>
#include <string>
#include "../../TokenClasses/token.h"
#include "../../TokenClasses/argumenttoken.h"

class CommandInStream : public InputStream 
{
    friend class CommandOutStream;

    private:
        std::vector<Token*> _command_args;

        void writeStream(const std::string& data);

    public:
	    CommandInStream();
    	std::vector<Token*> readStream() override;
	
};

inline CommandInStream::CommandInStream()
	: InputStream(InputStreamType::CommandInStream) {}

inline std::vector<Token*> CommandInStream::readStream() 
{
	return _command_args;
}

inline void CommandInStream::writeStream(const std::string& data) 
{
    _command_args.push_back(new ArgumentToken(data, 0));
}

#endif // COMMANDINSTREAM_H
