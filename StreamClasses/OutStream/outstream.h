#ifndef OUTSTREAM_H
#define OUTSTREAM_H

#include <string>
#include <iostream>
#include "../../config.h"

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


#endif // OUTSTREAM_H