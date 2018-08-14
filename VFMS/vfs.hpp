#ifndef FILE_STRUCTURE_HPP
#define FILE_STRUCTURE_HPP

#include <vector>
#include <iostream>

#include <boost/algorithm/string.hpp>

#include "file.hpp"

namespace vfms
{
    class vfs
    {
        // folder will be of the type vfs
        std::vector<vfms::vfs*> folders;
        // folder name for the current vfs
        std::string vfs_name;
        // a folder can contain files as well
        std::vector<vfms::file*> file;         


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
                if((**it).vfs_name == folder_name)
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
                std::cout << folder -> vfs_name << std::endl;
            }
            for(auto& file_name: this -> file)
            {
                std::cout << file_name -> get_file_name() << std::endl;
            }
        }

        // Go to folder
        vfs* go_to(std::string args)
        {
            vfs* go_to_folder = this;
            std::vector<std::string> folder_list;
            folder_list = 
                    boost::split(folder_list, args, boost::is_any_of("/"));
            
            for(auto&& folder_name: folder_list)
            {
                vfs* temp = go_to_folder;
                for(auto& folder: go_to_folder -> folders)
                {
                    if(folder -> vfs_name == folder_name)
                    {
                        go_to_folder = folder;
                        break;
                    }
                }
                if(go_to_folder == temp)
                {
                    std::cerr << "No directory exists by the name of "
                        << folder_name << std::endl;
                    return nullptr;
                }
            }

            return go_to_folder;
        }
    };
}

#endif /* FILE_STRUCTURE_HPP */