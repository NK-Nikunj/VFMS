#ifndef STRING_PARSER_HPP
#define STRING_PARSER_HPP

#include <vector>
#include <iostream>

// Includes all necessary
#include "command_map.hpp"
#include "file.hpp"

namespace vfms
{
    class string_parser
    {
        std::vector<std::string> arguments;

    public:
        // Initializing the arguments to process later
        string_parser(std::vector<std::string> arguments);

        // Process the arguments and evaluate
        vfms::vfs* process_args(vfms::vfs* current_folder);
    };
}

#endif /* STRING_PARSER_HPP */
