#include "validitychecker.h"
#include "../ExceptionClasses/exception.h"

void ValidityChecker::checkSemantic()
{
    if (_is_pipeline_cmd)
        return;

    bool has_input_redirect = false, has_output_redirect = false, has_args = false, has_opt = false;

    for (int i = 0; i < _tokens.size(); i++)
    {
        switch (_tokens[i]->type())
        {
            case Option:
                has_opt = true;
                if (has_input_redirect)
                    throw SyntaxException(InRedirect);
                if (has_output_redirect)
                    throw SyntaxException(OutRedirect);
                if (has_args)
                    throw SyntaxException(Argument);
                break;
            case Argument:
                has_args = true;
                if (has_input_redirect)
                    throw SyntaxException(InRedirect);
                if (has_output_redirect)
                    throw SyntaxException(OutRedirect);
                break;
            case InRedirect:
                has_input_redirect = true;
                break;
            case OutRedirect:
                has_output_redirect = true;
                break;
        }
    }

}

void ValidityChecker::checkFlow()
{
    bool has_input_redirect = false, has_output_redirect = false, has_args = false;

    for (int i = 0; i < _tokens.size(); i++)
    {
        TokenType curr_type = _tokens[i]->type();
        if (curr_type == Argument)
            has_args = true;
        else if (curr_type == InRedirect)
        {
            if (has_input_redirect || (_in_pipeline && _pos_in_pipeline != PosInPipeline::Start))
                throw SemanticFlowException(true);

            has_input_redirect = true;
        }
        else if (curr_type == OutRedirect)
        {
            if (has_output_redirect || (_in_pipeline && _pos_in_pipeline != PosInPipeline::End))
                throw SemanticFlowException(false);

            has_output_redirect = true;
        }
        else if (curr_type == CommandName)
        {
            _is_pipeline_cmd = true;
        }
    }

    if (has_args && has_input_redirect && !_is_pipeline_cmd)
        throw SemanticFlowException(true);
}

void ValidityChecker::checkSyntax()
{
    std::vector<int> errs, temp;

    for (int i = 0; i < _tokens.size(); i++)
    {
        temp = _tokens[i]->checkToken();

        errs.insert(errs.end(), temp.begin(), temp.end());
    }
    
    if (errs.size() != 0)
        throw SyntaxException(_original_line, errs);
}

void ValidityChecker::checkAll()
{
    checkFlow();
    checkSyntax();
    checkSemantic();
}

ValidityChecker::ValidityChecker(const std::vector<Token*>& tokens, const std::string& original_line, bool in_pipeline, PosInPipeline pos_in_pipeline)
    : _tokens(tokens), _original_line(original_line), _is_pipeline_cmd(false), _in_pipeline(in_pipeline), _pos_in_pipeline(pos_in_pipeline)
{
}
