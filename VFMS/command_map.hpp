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
}

#endif /* STRING_MAP_HPP */
