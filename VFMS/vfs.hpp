#ifndef FILE_STRUCTURE_HPP
#define FILE_STRUCTURE_HPP

#include <vector>
#include <iostream>
#include <tuple>

#include <boost/algorithm/string.hpp>

#include "file.hpp"

namespace vfms
{
    class vfs
    {
        vfms::vfs* parent_folder;
        // folder will be of the type vfs
        std::vector<vfms::vfs*> folders;
        // folder name for the current vfs
        std::string vfs_name;
        // a folder can contain files as well
        std::vector<vfms::file*> file;

        // Special aliases for 'cd' movement
        std::string folder_alias = ".";
        std::string parent_folder_alias = "..";

    public:

        // Set folder name
        void set_vfs_name(std::string vfs_name);

        // Get folder name
        std::string get_folder_name();

        // Move one step up in directory
        vfs* move_up();

        // Get parent_folder
        vfs* get_parent_folder();

        // Create folder
        vfs* create_folder(std::string folder_name);

        // Remove folder
        void remove_folder(std::string folder_name);

        // 'ls' command
        void show_content();

        // Go to folder
        vfs* go_to(std::string args, bool return_for_mkdir = false);

        // Go to folder containing file
        std::tuple<vfs*, std::string> go_to_file(std::string args);

        // Is folder
        bool is_folder(std::string name);

        // File status
        std::tuple<vfms::file*, bool> get_file(std::string file_name);
    };
}

#endif /* FILE_STRUCTURE_HPP */
