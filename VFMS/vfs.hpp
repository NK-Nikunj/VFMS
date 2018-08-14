#ifndef FILE_STRUCTURE_HPP
#define FILE_STRUCTURE_HPP

#include <vector>
#include <iostream>

#include "file.hpp"

namespace vfms
{
    class vfs
    {
        // folder will be of the type vfs
        std::vector<vfms::vfs> folders;
        // folder name for the current vfs
        std::string vfs_name;
        // a folder can contain files as well
        std::vector<vfms::file> file;         


    public:
        // Create folder
        vfs* create_folder(std::string folder_name)
        {
            vfs* new_folder = new vfs;
            new_folder -> vfs_name = folder_name;

            return new_folder;
        }

        // Remove folder
        void remove_folder(std::string folder_name)
        {
            auto it = this -> folders.begin();
            while(it != this -> folders.end())
            {
                if((*it).vfs_name == folder_name)
                    it = folders.erase(it);
                else
                    ++it;
            }
        }

        // 'ls' command
        void show_content()
        {
            for(auto& folder: this -> folders)
            {
                std::cout << folder.vfs_name << std::endl;
            }
            for(auto& file_name: this -> file)
            {
                std::cout << file_name.get_file_name << std::endl;
            }
        }

        // Go to folder
        vfs* const go_to(std::string args)
        {
            
        }
    };
}

#endif /* FILE_STRUCTURE_HPP */