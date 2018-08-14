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

        // Set folder name
        void set_vfs_name(std::string vfs_name)
        {
            this -> vfs_name = vfs_name;
            return;
        }

        // Create folder
        vfs* create_folder(std::string folder_name)
        {
            // Create a new folder pointer
            vfs* new_folder = new vfs;
            // push it to the current list of folders
            this -> folders.push_back(new_folder);
            // set folder name for new folder 
            new_folder -> vfs_name = folder_name;

            // Return pointer to new folder, in case needed
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
            if(!this -> folders.empty())
            {
                for(auto& folder: this -> folders)
                    std::cout << folder -> vfs_name << std::endl;
            }
            if(!this -> file.empty())
            {
                for(auto& file_name: this -> file)
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
            
            if(folder_list.size() == 1)
                return nullptr;

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