#ifndef PIPELINEPARSER_H
#define PIPELINEPARSER_H
#include <string>
#include <vector>
#include "../CommandClasses/command.hpp"
#include "../HelperClasses/iohelper.hpp"
#include "../config.hpp"
#include "../TokenClasses/token.hpp"
#include "parser.hpp"


class PipelineParser : public Parser
{
    public:
        PipelineParser(std::vector<Token*> tokens, InputStream* in_stream, OutStream* out_stream);
        virtual Command* parse();

    private:
        PosInPipeline _pos_in_pipeline;
};

#endif // PIPELINEPARSER_H