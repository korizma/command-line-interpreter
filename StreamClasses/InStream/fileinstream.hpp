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

#endif // FILEINSTREAM_H
