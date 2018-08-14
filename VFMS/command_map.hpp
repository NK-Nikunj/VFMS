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
        // TODO:
        // cp,
        // mv
    };

    // We store all the valid_commnads in an unordered map
    // for a fast access. Due to it's inline nature we require C++17
    inline std::unordered_map<std::string, commands> valid_commands = 
    {
        {"ls", commands::ls},
        { "mkdir", commands::mkdir },
        { "cd", commands::cd },
        { "touch", commands::touch },
        { "ned", commands::ned },
        { "cat", commands::cat },
    };
}

#endif /* STRING_MAP_HPP */