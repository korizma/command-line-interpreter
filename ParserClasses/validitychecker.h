#ifndef VALIDITYCHECKER_H
#define VALIDITYCHECKER_H

#include <vector>
#include <string>
#include "../TokenClasses/token.h"

class ValidityChecker 
{
    public:
        ValidityChecker(const std::vector<Token*>& tokens, const std::string& original_line);

        // Perform all checks (syntax, semantic, flow)
        void checkAll();

    private:
        std::vector<Token*> _tokens;
        std::string _original_line;
        bool _is_pipeline_cmd;

        // Individual checks
        void checkSyntax();
        void checkSemantic();
        void checkFlow();
};

#endif // VALIDITYCHECKER_H