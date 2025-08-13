
#ifndef FILEOUTSTREAM_H
#define FILEOUTSTREAM_H

#include "outstream.h"
#include <string>
#include "../../HelperClasses/iohelper.h"

class FileOutStream : public OutStream 
{
    private:
        std::string _filename;

    public:
        FileOutStream(const std::string& filename);

        void writeStream(const std::string& data) override;
};

inline FileOutStream::FileOutStream(const std::string& filename)
	: OutStream(OutStreamType::FileOutStream), _filename(filename) {}

inline void FileOutStream::writeStream(const std::string& data) 
{
    IOHelper io;
    io.writeFile(_filename, data);
}

#endif // FILEOUTSTREAM_H
