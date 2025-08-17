#include "command.h"


Command::~Command()
{
    if (_input_stream != NULL)
        delete _input_stream;
    if (_output_stream != NULL)
        delete _output_stream;
    if (_next_command != NULL)
        delete _next_command;
}

Command::Command(InputStream* inputStream, OutStream* outputStream, std::vector<Token*> options)
    : _input_stream(inputStream), _output_stream(outputStream), _options(options), _next_command(nullptr)
{
}

void Command::setNextCommand(Command* next)
{
    _next_command = next;
    _is_pipeline_cmd = true;
}

bool Command::needsInput() const
{
    return false;
}

bool Command::acceptsFileArgRead() const
{
    return false;
}

bool Command::hasOutputStream() const
{
    return true;
}

void Command::execute()
{
    _args = _input_stream->readStream();

    // sees if the command needs additional input
    if (needsInput() && _input_stream->getType() == InputStreamType::ArgInStream)
    {
        StdInStream temp = StdInStream();
        std::vector<Token*> temp_args = temp.readStream();
        _args.insert(_args.begin(), temp_args.begin(), temp_args.end());
    }

    isValid();

    // if the first arg is a file and the command can read it
    if (acceptsFileArgRead() && _args[0]->subType() == ArgFile)
    {
        IOHelper io;
        std::string filename = _args[0]->value();
        std::string content = io.readFile(filename);
        delete _args[0];
        _args[0] = new ArgumentToken("\"" + content + "\"", 0);
    }

    std::string output_text = getOutput();

    if (hasOutputStream() && !output_text.empty())
        _output_stream->writeStream(output_text);

    if (_next_command != NULL)
    {
        _next_command->execute();
    }
}


void Command::print()
{
    std::cout << "Command: ";
    for (const auto& arg : _args)
        arg->print();
    std::cout << "\nOptions: ";
    for (const auto& opt : _options)
        opt->print();


    _input_stream->print();
    _output_stream->print();

    if (_next_command != NULL)
    {
        std::cout << "Next command: " << std::endl;
        _next_command->print();
    }
    else
        std::cout << "No next command." << std::endl;
}

void Command::setInputStream(InputStream* input_stream)
{
    if (_input_stream != NULL)
        delete _input_stream;

    _input_stream = input_stream;
}

void Command::setOutputStream(OutStream* output_stream)
{
    Command* curr = this;
    while (curr->_next_command != NULL)
    {
        curr = curr->_next_command;
    }

    if (curr->_output_stream->getType() == OutStreamType::StdOutStream)
    {
        delete curr->_output_stream;
        curr->_output_stream = output_stream;
    }
}
