
#ifndef FILEOUTSTREAM_H
#define FILEOUTSTREAM_H

#include "outstream.h"
#include <string>
#include "../../HelperClasses/iohelper.h"

class FileOutStream : public OutStream 
{
    private:
        std::string _filename;
        bool _is_append;

    public:
        FileOutStream(const std::string& filename, bool is_append);

        void writeStream(const std::string& data) override;
};

inline FileOutStream::FileOutStream(const std::string& filename, bool is_append)
	: OutStream(OutStreamType::FileOutStream), _filename(filename), _is_append(is_append) {}

inline void FileOutStream::writeStream(const std::string& data) 
{
    IOHelper io;
    if (_is_append)
        io.appendFile(_filename, data);
    else
        io.writeFile(_filename, data);
}

#endif // FILEOUTSTREAM_H
