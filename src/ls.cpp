#include <VFMS/command/realize_command.hpp>

#include <vector>
#include <string>

namespace vfms
{
    extern struct command::command_stat* process_args(std::vector<std::string> args);

    class ls
    {
        command::command_stat stats;

    public:

    };

    void exec_ls(std::vector<std::string> args)
    {
        struct command::command_stat* obj = process_args(args);
    }
}