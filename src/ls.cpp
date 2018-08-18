#include <VFMS/command/realize_command.hpp>
#include <VFMS/command_map.hpp>
#include <VFMS/vfs.hpp>

#include <vector>
#include <string>
#include <unordered_map>

#include <boost/algorithm/string.hpp>

// #include <VFMS/command/ls.hpp>

namespace vfms
{
    namespace assets
    {
        extern void send_error(std::string error_for);
        extern void usage(std::string use_for);
    }

    extern struct command_line::command_stat* process_args(std::vector<std::string> args);

    // Currently we support only l and a for short formats
    enum ls_options_short
    {
        l,
        a,
    };

    // Currently we support only show all files and help formats
    enum ls_options_long
    {
        help,
        all,
    };

    std::unordered_map<std::string, ls_options_short> ls_short_tags =
    {
        {"l", ls_options_short::l},
        {"a", ls_options_short::a},
    };

    std::unordered_map<std::string, ls_options_long> ls_long_tags =
    {
        {"all", ls_options_long::all},
        {"help", ls_options_long::help},
    };

    struct ls
    {
        // store the info related to the command
        struct command_line::command_stat* obj;

        // Storing current folder
        vfs* current_folder;

        // short tags
        bool is_l;
        bool is_a;

        // long tags
        bool is_all;
        bool is_help;

        ls(vfs* current_folder, struct command_line::command_stat* obj)
        {
            this -> obj = obj;
            this -> current_folder = current_folder;

            is_l = false;
            is_a = false;
            is_all = false;
            is_help = false;
        }

        // Help user with the command usage
        void show_help()
        {
            std::cout << "ls: usage\n"
                        "ls [OPTION]... [FILE]...\n"
                        "List information about the FILEs\n"
                        "\nOptions:\n"
                        "\t-a, --all\t\tDo not ignore entries starting with .\n"
                        "\t-l\t\t\tUse long listing format\n"
                        "\t--help\t\t\tDisplay help text\n";
            
            return;
        }

        void write_a_l()
        {
            if(obj -> dir_name.size() == 0)
            {
                current_folder -> show_hidden_list_content();
            }
            else if(obj -> dir_name.size() == 1)
            {
                vfs* get_to_folder = 
                    current_folder -> go_to(obj -> dir_name.at(0));

                // check whether an error is raised
                if(get_to_folder != nullptr)
                    get_to_folder -> show_hidden_list_content();
            }
            else
            {
                // The command was not provided correctly
                assets::send_error("ls");
                assets::usage("ls");
                return;
            }
        }

        void write_a()
        {
            if(obj -> dir_name.size() == 0)
            {
                current_folder -> show_hidden_content();
            }
            else if(obj -> dir_name.size() == 1)
            {
                vfs* get_to_folder = 
                    current_folder -> go_to(obj -> dir_name.at(0));

                // check whether an error is raised
                if(get_to_folder != nullptr)
                    get_to_folder -> show_hidden_content();
            }
            else
            {
                // The command was not provided correctly
                assets::send_error("ls");
                assets::usage("ls");
                return;
            }
        }

        void write_l()
        {
            if(obj -> dir_name.size() == 0)
            {
                current_folder -> show_list_content();
            }
            else if(obj -> dir_name.size() == 1)
            {
                vfs* get_to_folder = 
                    current_folder -> go_to(obj -> dir_name.at(0));

                // check whether an error is raised
                if(get_to_folder != nullptr)
                    get_to_folder -> show_list_content();
            }
            else
            {
                // The command was not provided correctly
                assets::send_error("ls");
                assets::usage("ls");
                return;
            }
        }

        void write()
        {
            if(obj -> dir_name.size() == 0)
            {
                current_folder -> show_content();
            }
            else if(obj -> dir_name.size() == 1)
            {
                vfs* get_to_folder = 
                    current_folder -> go_to(obj -> dir_name.at(0));

                // check whether an error is raised
                if(get_to_folder != nullptr)
                    get_to_folder -> show_content();
            }
            else
            {
                // The command was not provided correctly
                assets::send_error("ls");
                assets::usage("ls");
                return;
            }
        }

        void process()
        {
            if(this -> is_help)
            {
                this -> show_help();
                return;
            }

            if(this -> is_a || this -> is_all)
            {
                if(this -> is_l)
                {
                    this -> write_a_l();
                }
                else
                {
                    this -> write_a();
                }
            }
            else if(this -> is_l)
            {
                this -> write_l();
            }
            else
            {
                this -> write();
            }
        }
    };

    std::vector<std::string> get_short_tags(std::string args, struct ls& ls_object)
    {
        std::vector<std::string> null;

        if(args.empty())
            return null;

        std::vector<std::string> short_args;

        std::string single_char;
        // split about every character
        for(auto&& character: args)
        {
            single_char = character;
            short_args.push_back(single_char);
        }

        // initializing the enum object
        ls_options_short tag;

        try
        {
            for(auto&& arg: short_args)
            {
                tag = ls_short_tags.at(arg);

                switch(tag) 
                {
                    case l:
                        ls_object.is_l = true;
                        break;
                    case a:
                        ls_object.is_a = true;
                        break;
                }
            }    
        } catch(...)
        {
            std::string command = "ls";
            assets::send_error(command);
            assets::usage(command);

            return null;
        }

        return short_args;
    }

    void exec_ls(std::vector<std::string> args, vfs* current_folder)
    {   
        struct command_line::command_stat* obj = process_args(args);

        if(obj == nullptr)
        {
                std::string command = "ls";
                assets::send_error(command);
                assets::usage(command);

                return;
        }

        struct ls ls_object(current_folder, obj);

        if(ls_object.obj == nullptr)
        {
            // The command was not provided correctly
            assets::send_error(args.at(0));
            assets::usage(args.at(0));
            return;
        }
        else
        {
            if(!ls_object.obj -> partial_help_tag.empty())
            {
                // Some short tags can be used in conjunction. We need
                // to distinguish them form each other.
                std::vector<std::string> short_tags = get_short_tags(ls_object.obj -> partial_help_tag, std::ref(ls_object));
            
                if(short_tags.empty())
                    return;
            }

            // initializing the enum object
            ls_options_long tag;

            try
            {   if(!obj -> complete_help_tag.empty())
                {   
                    for(auto&& arg: ls_object.obj -> complete_help_tag)
                    {
                        
                        tag = ls_long_tags.at(arg);

                        switch(tag) 
                        {
                            case all:
                                ls_object.is_all = true;
                                break;
                            case help:
                                ls_object.is_help = true;
                                break;
                        }
                    }
                }    
            } catch(...)
            {
                std::string command = "ls";
                assets::send_error(command);
                assets::usage(command);

                return;
            }

            ls_object.process();
        }
    }
}