#ifndef STRING_PARSER_HPP
#define STRING_PARSER_HPP

#include <vector>
#include <iostream>

// Includes all necessary
#include "command_map.hpp"

namespace vfms
{
    class string_parser
    {
        std::vector<std::string> arguments;

    public:
        // Initializing the arguments to process later
        string_parser(std::vector<std::string> arguments)
        {
            for(auto&& args: arguments)
            {
                this -> arguments.push_back(args);
            }
        }

        // Process the arguments and evaluate
        void process_args(vfms::vfs* current_folder)
        {
            commands command_type;
            // unordered_map returns an exception if it doesn't find any element.
            try
            {
                command_type = valid_commands.at(this -> arguments[0]);
            } catch (...)
            {
                // Command could not be found in the list of valid command.
                std::cerr << this -> arguments[0] << " is not a valid command." << std::endl;
                return;
            }

            switch(command_type)
            {
                case ls:
                    if(this -> arguments.size() == 1)
                    {
                        current_folder -> show_content();
                    } else if(this -> arguments.size() == 2)
                    {
                        vfms::vfs* get_to_folder =
                                        current_folder -> go_to(this -> arguments[1]);
                        get_to_folder -> show_content();
                    } else
                    {
                        std::cerr << "Wrong use of command 'ls'." << std::endl;
                    }
                    break;
                
                case mkdir:
                    break;
                
                case cd:
                    break;
                
                case touch:
                    break;
                
                case ned:
                    break;
            }
        }
    };
}

#endif /* STRING_PARSER_HPP */