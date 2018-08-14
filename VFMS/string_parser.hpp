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
            // If user did not add any arguments, simply move ahead.
            if(this -> arguments.size())
                return;

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
                        // Since argument count is 1, simply show contents from current
                        // directory.
                        current_folder -> show_content();
                    } else if(this -> arguments.size() == 2)
                    {
                        // Move to the specified directory. If there is none then raise
                        // alert that the folder does not exists.
                        vfms::vfs* get_to_folder =
                                        current_folder -> go_to(this -> arguments[1]);
                        
                        // Check if an error was raised
                        if(get_to_folder != nullptr)
                            get_to_folder -> show_content();
                    } else
                    {   
                        // Incorrect usage of the command. Raise an error.
                        std::cerr << "Wrong use of command 'ls'.\n"
                            "Usage: ls path/to/directory" << std::endl;
                    }
                    break;
                
                case mkdir:
                    if(this -> arguments.size() == 1)
                    {
                        // Incorrect usage of mkdir. Raise an error.
                        std::cerr << "Wrong use of command 'mkdir'.\n"
                            "Usage: mkdir dir1 dir2 dir3" << std::endl;
                        return;
                    } else
                    {
                        for(int i = 1; i != this -> arguments.size(); ++i)
                        {
                            // Move to the specified directory. If there is 
                            // none then raise alert that the folder 
                            // does not exists.
                            vfms::vfs* get_to_folder =
                                current_folder -> go_to(this -> arguments[i]);

                            if(get_to_folder == nullptr)
                                current_folder -> create_folder(this -> arguments[i]);
                            else
                                get_to_folder -> create_folder(this -> arguments[i]);
                        }
                    }
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