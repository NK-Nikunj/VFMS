#include <VFMS/command/realize_command.hpp>
#include <VFMS/command_map.hpp>
#include <VFMS/vfs.hpp>

#include <vector>
#include <string>
#include <unordered_map>

#include <boost/algorithm/string.hpp>

namespace vfms
{
    namespace assets
    {
        extern void send_error(std::string error_for);
        extern void usage(std::string use_for);
    }

    extern struct command_line::command_stat* process_args(std::vector<std::string> args);

    // Currently we support only help formats
    enum cd_options_long
    {
        help,
    };

    // Mapping help tag with enum
    std::unordered_map<std::string, cd_options_long> cd_long_tags =
    {
        {"help", cd_options_long::help},
    };

    struct cd
    {
        // store the info related to the command
        struct command_line::command_stat* obj;

        // Storing current folder
        vfs* current_folder;

        // long tags
        bool is_help;

        cd(vfs* current_folder, struct command_line::command_stat* obj)
        {
            this -> obj = obj;
            this -> current_folder = current_folder;

            this -> is_help = false;
        }

        void show_help()
        {
            std::cout << "cd: usage\n"
                        "cd [OPTION]... [FILE]...\n"
                        "Creates Directory at the listed location.\n"
                        "\nOptions:\n"
                        "\t--help\t\t\tDisplay help text\n";
            
            return;
        }

        void process()
        {
            if(this -> is_help)
            {
                this -> show_help();
                return;
            }

            if(obj -> dir_name.size() != 0)
            {
                vfs* get_to_folder =
                    current_folder -> go_to(obj -> dir_name.at(0));
                if(get_to_folder != nullptr)
                {
                    // Make directory in a different folderget_to_folder -> create_folder(obj -> dir_name.at(obj -> dir_name.size() - 1));
                    this -> current_folder = get_to_folder;
                }
            }
            else
            {
                // The command was not provided correctly
                assets::send_error("cd");
                assets::usage("cd");
                return;
            }
        }
    };

    vfs* exec_cd(std::vector<std::string> args, vfs* current_folder)
    {   
        struct command_line::command_stat* obj = process_args(args);

        if(obj == nullptr)
        {
                std::string command = "cd";
                assets::send_error(command);
                assets::usage(command);

                return nullptr;
        }

        struct cd cd_object(current_folder, obj);

        if(cd_object.obj == nullptr)
        {
            // The command was not provided correctly
            assets::send_error(args.at(0));
            assets::usage(args.at(0));
            return nullptr;
        }
        else
        {
            if(!cd_object.obj -> partial_help_tag.empty())
            {
                assets::send_error((std::string)"cd");
                assets::usage((std::string)"cd");
                return nullptr;
            }

            // initializing the enum object
            cd_options_long tag;

            try
            {   if(!obj -> complete_help_tag.empty())
                {   
                    for(auto&& arg: cd_object.obj -> complete_help_tag)
                    {
                        
                        tag = cd_long_tags.at(arg);

                        switch(tag) 
                        {
                            case help:
                                cd_object.is_help = true;
                                break;
                        }
                    }
                }    
            } catch(...)
            {
                std::string command = "cd";
                assets::send_error(command);
                assets::usage(command);

                return nullptr;
            }

            cd_object.process();
            return cd_object.current_folder;
        }
    }
}