#pragma once

#define PATHSIGN "$"
#define MAXLINELEN 512
#define ARGALLOWEDCHRS "/_.-"

enum TokenType
{
    Arg,
    Option,
    InRedirect,
    OutRedirect,
    PipeSign
};