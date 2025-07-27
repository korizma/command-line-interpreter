#pragma once

#define PATHSIGN "$"
#define MAXLINELEN 512

enum TokenType
{
    Arg,
    Option,
    InRedirect,
    OutRedirect,
    PipeSign
};