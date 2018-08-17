#include <VFMS/command/ls.hpp>
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

        for(int i = 1; i < args.size(); ++i)
        {
            std::string help_tag = "-";
            std::string escape_character = "\\";

            /* There are can be 3 type of arguments.
                1. Directories/file
                2. partial helper tag (ex: ls -la)
                3. Complete helper tags (ex: ls --help)
            */
            try
            {
                // Check if it is a helper tag
                if(args.at(i).at(0) == help_tag)
                {
                    if(args.at(i).at(1) != help_tag)
                        stats -> partial_help_tag.push_back(args.at(i).substr(help_tag));
                    else
                        stats -> complete_help_tag.push_back(args.at(i).substr(help_tag + help_tag));
                }
                // It is a directory
                else
                {
                    // Starting off with an empty path
                    std::string dir_name = "";
                    if(args.at(i).at(args.at(i).size() - 1) != escape_character)
                    {
                        dir_name.append(args.at(i));
                    }
                    else
                    {
                        // Get complete path to the file/directory
                        while(args.at(i).at(args.at(i).size() - 1) == escape_character)
                        {
                            dir_name.append(args.at(i).substr(0, args.at(i).size() - 2));
                            dir_name.append(" ");
                            i++;
                        }
                        // Complete path to the file/directory
                        dir_name = dir_name.substr(0, dir_name.size() - 2);
                        i--;    // Since we increment i, we need decrement to get back to actual i
                    }

                    stats -> dir_name.push_back(dir_name);
                }
            }
            catch(...)
            {
                return nullptr;
            }
        }

        // Technical knowledge about the arguments received
        return stats;
    }
}