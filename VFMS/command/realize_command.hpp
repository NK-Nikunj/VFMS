#ifndef REALIZE_COMMAND_HPP
#define REALIZE_COMMAND_HPP

#include <string>
#include <vector>

namespace vfms
{
    namespace command
    {
        // Contains all the necessary details for understanding
        // the command.
        struct command_stat
        {
            std::vector<std::string> complete_help_tag;
            std::vector<std::string> partial_help_tag;
            std::vector<std::string> dir_name;
        };
    }
}

#endif /* REALIZE_COMMAND_HPP */