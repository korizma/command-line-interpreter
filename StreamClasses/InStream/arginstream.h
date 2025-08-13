#ifndef ARGINSTREAM_H
#define ARGINSTREAM_H

#include "inputstream.h"
#include <vector>
#include <string>
#include "../TokenClasses/token.h"
#include "../TokenClasses/argumenttoken.h"
#include "../../HelperClasses/iohelper.h"

class ArgInStream : public InputStream 
{
    private:
        std::vector<Token*> _args;

    public:
        ArgInStream(const std::vector<Token*>& arguments);

        std::vector<Token*> readStream() override;
};

inline ArgInStream::ArgInStream(const std::vector<Token*>& arguments)
    : InputStream(InputStreamType::ArgInStream), _args(arguments) {}

inline std::vector<Token*> ArgInStream::readStream() 
{
    return _args;
}



#endif // ARGINSTREAM_H