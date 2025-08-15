
#ifndef COMMANDINSTREAM_H
#define COMMANDINSTREAM_H

#include "inputstream.h"
#include <vector>
#include <string>
#include "../../TokenClasses/token.h"
#include "../../TokenClasses/argumenttoken.h"

class CommandInStream : public InputStream 
{
    private:
        std::vector<Token*> _command_args;

    public:
	    CommandInStream();
    	std::vector<Token*> readStream() override;

        void print() const override;

        void addArgs(Token* arg);

        void writeStream(const std::string& data);

};

#endif // COMMANDINSTREAM_H
