#include <unordered_map>
#include <iostream>

#include "../VFMS/command_map.hpp"

namespace vfms
{
    // We store all the valid_commnads in an unordered map
    std::unordered_map<std::string, commands> valid_commands = 
    {
        {"ls", commands::ls},
        { "mkdir", commands::mkdir },
        { "cd", commands::cd },
        { "touch", commands::touch },
        { "ned", commands::ned },
        { "cat", commands::cat },
        { "quit", commands::quit },
    };
}