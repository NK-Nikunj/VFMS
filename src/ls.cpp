#include <VFMS/command/realize_command.hpp>
#include <VFMS/command_map.hpp>

#include <vector>
#include <string>
#include <unordered_map>

#include <VFMS/command/ls.hpp>

namespace vfms
{
    namespace assets
    {
        extern void send_error(std::string error_for);
        extern void usage(std::string use_for);
    }

    extern struct command::command_stat* process_args(std::vector<std::string> args);

    std::unordered_map<std::string, command::ls_options_short> ls_short_tags =
    {
        {"l", command::ls_options_short::l},
        {"a", command::ls_options_short::a},
    };

    std::unordered_map<std::string, command::ls_options_long> ls_long_tags =
    {
        {"all", command::ls_options_long::all},
        {"help", command::ls_options_long::help},
    };

    class ls
    {
        command::command_stat stats;

    public:

    };

    void exec_ls(std::vector<std::string> args)
    {
        struct command::command_stat* obj = process_args(args);

        if(obj == nullptr)
        {
            // The command was not provided correctly
            assets::send_error(args.at(0));
            assets::usage(args.at(0));
            return;
        }
        else
        {
            
        }
    }
}