
#ifndef FILEINSTREAM_H
#define FILEINSTREAM_H

#include "inputstream.hpp"
#include <vector>
#include <string>
#include <fstream>
#include "../../TokenClasses/token.hpp"
#include "../../TokenClasses/argumenttoken.hpp"
#include "../../HelperClasses/iohelper.hpp"

class FileInStream : public InputStream 
{
    private:
        std::string _filename;

    public:
        FileInStream(const std::string& filename);

        std::vector<Token*> readStream() override;
};

inline FileInStream::FileInStream(const std::string& filename)
	: InputStream(InputStreamType::FileInStream), _filename(filename) {}



inline std::vector<Token*> FileInStream::readStream() 
{
	std::vector<Token*> tokens;
    IOHelper io;
    std::string input = "\"" + io.readFile(_filename) + "\"";
    tokens.push_back(new ArgumentToken(input, 0));
    return tokens;
}

#endif // FILEINSTREAM_H
