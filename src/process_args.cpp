#include <VFMS/command/realize_command.hpp>
#include <VFMS/command_map.hpp>

#include <unordered_map>
#include <vector>
#include <string>

#include <boost/algorithm/string.hpp>

namespace vfms
{
    extern std::unordered_map<std::string, commands> valid_commands;

    struct command::command_stat* process_args(std::vector<std::string> args)
    {
        struct command::command_stat* stats = new struct command::command_stat;

        commands command_type;
        // unordered_map returns an exception if it doesn't find any element.
        try
        {
            command_type = valid_commands.at(args[0]);
        } catch (...)
        {
            // Command could not be found in the list of valid command.
            std::cerr << args[0] << " is not a valid command." << std::endl;
            return nullptr;
        }

        for(int i = 1; i < args.size(); ++i)
        {
            std::string dash = "-";
            if(args[i].at(0) == dash.at(0))
            {
                try
                {
                    if(args[i].at(1) == dash.at(0))
                    {

                    }
                }
                catch(...)
                {
                    std::cerr << "Could not understand the command." << std::endl;
                    return nullptr;
                }
            }
        }
    }
}