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
    enum mkdir_options_long
    {
        help,
    };

    // Mapping help tag with enum
    std::unordered_map<std::string, mkdir_options_long> mkdir_long_tags =
    {
        {"help", mkdir_options_long::help},
    };

    struct mkdir
    {
        // store the info related to the command
        struct command_line::command_stat* obj;

        // Storing current folder
        vfs* current_folder;

        // long tags
        bool is_help;

        mkdir(vfs* current_folder, struct command_line::command_stat* obj)
        {
            this -> obj = obj;
            this -> current_folder = current_folder;

            this -> is_help = false;
        }

        void show_help()
        {
            std::cout << "mkdir: usage\n"
                        "mkdir [OPTION]... [FILE]...\n"
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
                    current_folder -> go_to(obj -> dir_name.at(0), true);
                if(get_to_folder == current_folder)
                {
                    // Make directory in the current folder
                    current_folder -> create_folder(obj -> dir_name.at(obj -> dir_name.size() - 1));
                } else if(get_to_folder != nullptr)
                {
                    // Make directory in a different folder
                    get_to_folder -> create_folder(obj -> dir_name.at(obj -> dir_name.size() - 1));
                }
            }
            else
            {
                // The command was not provided correctly
                assets::send_error("mkdir");
                assets::usage("mkdir");
                return;
            }
        }
    };

    void exec_mkdir(std::vector<std::string> args, vfs* current_folder)
    {   
        struct command_line::command_stat* obj = process_args(args);

        if(obj == nullptr)
        {
                std::string command = "mkdir";
                assets::send_error(command);
                assets::usage(command);

                return;
        }

        struct mkdir mkdir_object(current_folder, obj);

        if(mkdir_object.obj == nullptr)
        {
            // The command was not provided correctly
            assets::send_error(args.at(0));
            assets::usage(args.at(0));
            return;
        }
        else
        {
            if(!mkdir_object.obj -> partial_help_tag.empty())
            {
                assets::send_error((std::string)"mkdir");
                assets::usage((std::string)"mkdir");
                return;
            }

            // initializing the enum object
            mkdir_options_long tag;

            try
            {   if(!obj -> complete_help_tag.empty())
                {   
                    for(auto&& arg: mkdir_object.obj -> complete_help_tag)
                    {
                        
                        tag = mkdir_long_tags.at(arg);

                        switch(tag) 
                        {
                            case help:
                                mkdir_object.is_help = true;
                                break;
                        }
                    }
                }    
            } catch(...)
            {
                std::string command = "mkdir";
                assets::send_error(command);
                assets::usage(command);

                return;
            }

            mkdir_object.process();
        }
    }
}