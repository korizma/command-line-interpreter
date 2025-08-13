#ifndef STDOUTSTREAM_H
#define STDOUTSTREAM_H

#include "outstream.h"
#include <iostream>

class StdOutStream : public OutStream 
{
    public:
        StdOutStream() : OutStream(OutStreamType::StdOutStream) {}

        virtual void writeStream(const std::string& data) override; 
};

inline void StdOutStream::writeStream(const std::string& data) 
{
    std::cout << data << std::endl;
}

#endif // STDOUTSTREAM_H