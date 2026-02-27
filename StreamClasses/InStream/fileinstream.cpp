#include "fileinstream.hpp"
#include "../../HelperClasses/iohelper.hpp"
#include "../../TokenClasses/argumenttoken.hpp"

FileInStream::FileInStream(const std::string& filename)
    : InputStream(InputStreamType::FileInStream), _filename(filename) {}

std::vector<Token*> FileInStream::readStream() {
    std::vector<Token*> tokens;
    IOHelper io;
    std::string input = "\"" + io.readFile(_filename) + "\"";
    tokens.push_back(new ArgumentToken(input, 0));
    return tokens;
}
