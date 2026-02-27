#include "arginstream.hpp"

ArgInStream::ArgInStream(const std::vector<Token*>& arguments)
    : InputStream(InputStreamType::ArgInStream), _args(arguments) {}

std::vector<Token*> ArgInStream::readStream() {
    return _args;
}

int ArgInStream::getArgCount() const {
    return _args.size();
}
