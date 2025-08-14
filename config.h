#pragma once

#define PATHSIGN "$"
#define MAXLINELEN 512
#define ARGALLOWEDCHRS "/_.-"


enum TokenType
{
    Argument,
    Option,
    InRedirect,
    OutRedirect,
    CommandName
};

enum SubTokenType
{
    ArgString,
    ArgFile,
    OutWrite,
    OutAppend,
    SubTokenNone
};

enum class InputStreamType
{
    ArgInStream,
    FileInStream,
    StdInStream,
    CommandInStream
};

enum class OutStreamType
{
    CommandOutStream,
    FileOutStream,
    StdOutStream
};

