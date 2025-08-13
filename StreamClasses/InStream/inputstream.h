#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

#include <string>
#include <vector>
#include "../TokenClasses/token.h"
#include "../config.h"

class InputStream 
{
    private:
        InputStreamType _type;

    public:
        InputStream(InputStreamType type) : _type(type) {}

        virtual std::vector<Token*> readStream() = 0;

        InputStreamType getType() const { return _type; }

        virtual void print() const;

};

inline void InputStream::print() const
{
    switch (_type)
    {
        case InputStreamType::StdInStream:
            std::cout << "InputStream Type: STDIN" << std::endl;
            break;
        case InputStreamType::FileInStream:
            std::cout << "InputStream Type: FILE" << std::endl;
            break;
        case InputStreamType::ArgInStream:
            std::cout << "InputStream Type: ARG" << std::endl;
            break;
        case InputStreamType::CommandInStream:
            std::cout << "InputStream Type: COMMAND" << std::endl;
            break;
    }
}

#endif // INPUTSTREAM_H