#ifndef ARGINSTREAM_H
#define ARGINSTREAM_H

#include "inputstream.hpp"
#include <vector>
#include <string>
#include "../../TokenClasses/token.hpp"
#include "../../TokenClasses/argumenttoken.hpp"
#include "../../HelperClasses/iohelper.hpp"

class ArgInStream : public InputStream 
{
    private:
        std::vector<Token*> _args;

    public:
        ArgInStream(const std::vector<Token*>& arguments);

        std::vector<Token*> readStream() override;

        int getArgCount() const;
};

inline ArgInStream::ArgInStream(const std::vector<Token*>& arguments)
    : InputStream(InputStreamType::ArgInStream), _args(arguments) {}

inline std::vector<Token*> ArgInStream::readStream() 
{
    return _args;
}

inline int ArgInStream::getArgCount() const
{
    return _args.size();
}

#endif // ARGINSTREAM_H