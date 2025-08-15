
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
    friend class Parser;

    private:
        std::vector<Token*> _command_args;

        void writeStream(const std::string& data);

        void addArgs(Token* arg);

    public:
	    CommandInStream();
    	std::vector<Token*> readStream() override;

        void print() const override;

};

#endif // COMMANDINSTREAM_H
