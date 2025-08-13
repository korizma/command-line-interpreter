#ifndef OUTSTREAM_H
#define OUTSTREAM_H

#include <string>
#include <iostream>
#include "../config.h"

class OutStream 
{
    private:
        OutStreamType _type;

    public:
        OutStream(OutStreamType type);

        OutStreamType getType() const;

        virtual void writeStream(const std::string& data) = 0;

        virtual void print() const;
};

inline OutStream::OutStream(OutStreamType type)
    : _type(type) {}

    OutStreamType OutStream::getType() const
{
    return _type;
}

inline void OutStream::print() const
{
    switch (_type)
    {
        case OutStreamType::CommandOutStream:
            std::cout << "OutStream Type: COMMAND" << std::endl;
            break;
        case OutStreamType::FileOutStream:
            std::cout << "OutStream Type: FILE" << std::endl;
            break;
        case OutStreamType::StdOutStream:
            std::cout << "OutStream Type: STDOUT" << std::endl;
            break;
    }
}

#endif // OUTSTREAM_H