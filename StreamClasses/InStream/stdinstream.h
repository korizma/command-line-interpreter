
#ifndef CLIINSTREAM_H
#define CLIINSTREAM_H

#include "inputstream.h"
#include <vector>
#include <string>
#include "../TokenClasses/token.h"
#include "../../HelperClasses/iohelper.h"
#include "../TokenClasses/argumenttoken.h" 

class StdInStream : public InputStream 
{
    public:
        StdInStream();

        std::vector<Token*> readStream() override;
};

inline StdInStream::StdInStream()
    : InputStream(InputStreamType::StdInStream) {}

inline std::vector<Token*> StdInStream::readStream() 
{
    IOHelper io;
    std::vector<Token*> tokens;
    Token* input_token = new ArgumentToken("\'" + io.getLine() + "\'", 0);

    tokens.push_back(input_token);
    return tokens;
}



#endif // CLIINSTREAM_H