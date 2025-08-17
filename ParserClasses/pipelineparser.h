#ifndef PIPELINEPARSER_H
#define PIPELINEPARSER_H
#include <string>
#include <vector>
#include "../CommandClasses/command.h"
#include "../HelperClasses/iohelper.h"
#include "../config.h"
#include "../TokenClasses/token.h"
#include "parser.h"


class PipelineParser : public Parser
{
    public:
        PipelineParser(std::vector<Token*> tokens, InputStream* in_stream, OutStream* out_stream);
        virtual Command* parse();

    private:
        PosInPipeline _pos_in_pipeline;
};

#endif // PIPELINEPARSER_H