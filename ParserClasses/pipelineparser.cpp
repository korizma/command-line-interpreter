#include "pipelineparser.hpp"
#include "../StreamClasses/InStream/arginstream.hpp"
#include "../StreamClasses/InStream/arginstream.hpp"
#include "../StreamClasses/OutStream/commandoutstream.hpp"
#include "validitychecker.hpp"


PipelineParser::PipelineParser(std::vector<Token*> tokens, InputStream* in_stream, OutStream* out_stream)
    : Parser()
{
    _command_token = tokens[0];
    _cmd_tokens.assign(tokens.begin() + 1, tokens.end());
    _input_redirect = in_stream;
    _output_redirect = out_stream;

    if (in_stream == NULL)
        _pos_in_pipeline = PosInPipeline::Start;
    else if (out_stream == NULL)
        _pos_in_pipeline = PosInPipeline::End;
    else
        _pos_in_pipeline = PosInPipeline::Middle;
}

Command* PipelineParser::parse()
{
    ValidityChecker checker = ValidityChecker(_cmd_tokens, _command_token->value(), true, _pos_in_pipeline);
    checker.checkAll();

    classifyTokens();

    if (_input_redirect == NULL)
        _input_redirect = new ArgInStream(_args);

    if (_input_redirect->getType() == InputStreamType::CommandInStream)
    {
        CommandInStream* command_in_stream = dynamic_cast<CommandInStream*>(_input_redirect);
        for (int i = 0; i < _args.size(); i++)
        {
            command_in_stream->addArgs(_args[i]);
        }
    }

    createCommand();

    if (!_final_command->hasOutputStream() && _pos_in_pipeline != PosInPipeline::End)
        throw PipelineException(_command_token->value());

    return _final_command;    
}