#ifndef STRING_PARSER_HPP
#define STRING_PARSER_HPP

#include <vector>
#include <iostream>

// Includes all necessary
#include <VFMS/command_map.hpp>
#include <VFMS/file.hpp>
#include <VFMS/vfs.hpp>

namespace vfms
{
    extern std::unordered_map<std::string, commands> valid_commands;

    class string_parser
    {
        std::vector<std::string> arguments;

    public:
        string_parser(std::vector<std::string> arguments);

        // Process the arguments and evaluate
        vfs* process_args(vfs* current_folder);
    };
}

#endif /* STRING_PARSER_HPP */
