#ifndef VALIDITYCHECKER_H
#define VALIDITYCHECKER_H

#include <vector>
#include <string>
#include "../TokenClasses/token.h"

class ValidityChecker 
{
    public:
        ValidityChecker(const std::vector<Token*>& tokens, const std::string& original_line, bool in_pipeline = false, PosInPipeline pos_in_pipeline = PosInPipeline::Start);

        // Perform all checks (syntax, semantic, flow)
        void checkAll();

    private:
        std::vector<Token*> _tokens;
        std::string _original_line;
        bool _is_pipeline_cmd;
        bool _in_pipeline;
        PosInPipeline _pos_in_pipeline;

        // Individual checks
        void checkSyntax();
        void checkSemantic();
        void checkFlow();
};

#endif // VALIDITYCHECKER_H