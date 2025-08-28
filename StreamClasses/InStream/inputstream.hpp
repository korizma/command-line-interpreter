#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

#include <string>
#include <vector>
#include "../../TokenClasses/token.hpp"
#include "../../config.hpp"

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



#endif // INPUTSTREAM_H