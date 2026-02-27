#include "inputstream.hpp"
#include <iostream>

void InputStream::print() const {
    switch (_type) {
        case InputStreamType::StdInStream:
            std::cout << "InputStream Type: STDIN" << std::endl;
            break;
        case InputStreamType::FileInStream:
            std::cout << "InputStream Type: FILE" << std::endl;
            break;
        case InputStreamType::ArgInStream:
            std::cout << "InputStream Type: ARG" << std::endl;
            break;
        case InputStreamType::CommandInStream:
            std::cout << "InputStream Type: COMMAND" << std::endl;
            break;
    }
}
