#include "outstream.hpp"

OutStream::OutStream(OutStreamType type)
    : _type(type) {}

    OutStreamType OutStream::getType() const
{
    return _type;
}

void OutStream::print() const
{
    switch (_type)
    {
        case OutStreamType::CommandOutStream:
            std::cout << "OutStream Type: COMMAND" << std::endl;
            break;
        case OutStreamType::FileOutStream:
            std::cout << "OutStream Type: FILE" << std::endl;
            break;
        case OutStreamType::StdOutStream:
            std::cout << "OutStream Type: STDOUT" << std::endl;
            break;
    }
}