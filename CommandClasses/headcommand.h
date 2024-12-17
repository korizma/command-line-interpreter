#ifndef HEADCOMMAND_H
#define HEADCOMMAND_H

#include <command.h>
#include <iostream>
#include <string>


class HeadCommand : public Command 
{
    private:
        virtual void isValid() override;
        static std::vector<std::string> getNLines(std::string text, int n);

    public:
        HeadCommand(const std::string& original_command, const std::vector<std::string>& arguments, const std::vector<std::string>& options, const std::string& in_filename, const std::string& out_filename)
                : Command(original_command, arguments, options, in_filename, out_filename) {}
        ~HeadCommand();

        virtual void execute() override;

        static std::string getType();
};
#endif // HEADCOMMAND_H