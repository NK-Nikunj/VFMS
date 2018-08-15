#ifndef STRING_MAP_HPP
#define STRING_MAP_HPP

#include <unordered_map>
#include <iostream>

namespace vfms
{
    // List of all valid commands allowed to user
    enum commands
    {
        ls,
        mkdir,
        cd,
        touch,
        ned,
        cat,
        quit,
        // TODO:
        // cp,
        // mv
    };

    inline std::unordered_map<std::string, commands> valid_commands = 
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

#endif /* STRING_MAP_HPP */
