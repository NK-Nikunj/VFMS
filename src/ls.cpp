#include <VFMS/command/realize_command.hpp>
#include <VFMS/command_map.hpp>

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
        // short tags
        bool is_l;
        bool is_a;

        // long tags
        bool is_all;
        bool is_help;

        ls()
        {
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
                        "\t-l\t\tUse long listing format\n"
                        "\t--help\t\tDisplay help text\n";
            
            return;
        }

        void list_down()
        {
            if(this -> is_a || this -> is_all)
            {
                if(this -> is_l)
                {

                }
            }
        }

        void process()
        {
            if(this -> is_help)
            {
                this -> show_help();
                return;
            }

            this -> list_down();
        }
    };

    std::vector<std::string> get_short_tags(std::string args, struct ls ls_object)
    {
        std::vector<std::string> short_args;

        // split about every character
        short_args = boost::split(short_args, args, boost::is_any_of(""));

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

            std::vector<std::string> null;
            return null;
        }

        return short_args;
    }

    void exec_ls(std::vector<std::string> args)
    {
        struct command_line::command_stat* obj = process_args(args);

        struct ls ls_object;

        if(obj == nullptr)
        {
            // The command was not provided correctly
            assets::send_error(args.at(0));
            assets::usage(args.at(0));
            return;
        }
        else
        {
            // Some short tags can be used in conjunction. We need
            // to distinguish them form each other.
            std::vector<std::string> short_tags = get_short_tags(obj -> partial_help_tag, ls_object);
        
            // initializing the enum object
            ls_options_long tag;

            try
            {
                for(auto&& arg: obj -> complete_help_tag)
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
            } catch(...)
            {
                std::string command = "ls";
                assets::send_error(command);
                assets::usage(command);

                return;
            }

            if(!short_tags.empty() && !obj -> partial_help_tag.empty())
            {
                ls_object.process();
            }
        }
    }
}