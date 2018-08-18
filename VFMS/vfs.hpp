#ifndef FILE_STRUCTURE_HPP
#define FILE_STRUCTURE_HPP

#include <vector>
#include <iostream>
#include <tuple>

#include <boost/algorithm/string.hpp>

#include <VFMS/file.hpp>

namespace vfms
{
    class vfs
    {
        vfms::vfs* parent_folder;
        // folder will be of the type vfs
        std::vector<vfms::vfs*> folders;
        // hidden folders be of the type vfs
        std::vector<vfms::vfs*> hidden_folders;
        // folder name for the current vfs
        std::string vfs_name;
        // a folder can contain files as well
        std::vector<vfms::file*> file;
        // a folder can contain files as well
        std::vector<vfms::file*> hidden_file;

        // Special aliases for 'cd' movement
        std::string folder_alias = ".";
        std::string parent_folder_alias = "..";

    public:

        // Set folder name
        void set_vfs_name(std::string vfs_name)
        {
            this -> vfs_name = vfs_name;
            return;
        }

        // Get folder name
        std::string get_folder_name()
        {
            // Returns the name of the current folder
            return this -> vfs_name;
        }

        // Move one step up in directory
        vfs* move_up()
        {
            if(this == nullptr)
                return nullptr;
            
            return this -> parent_folder;
        }

        // Get parent_folder
        vfs* get_parent_folder()
        {
            // Returns the parent folder address
            return this -> parent_folder;
        }

        // Create folder
        vfs* create_folder(std::string folder_name)
        {
            // Check whether folder/file with same name exists
            if(!this -> folders.empty())
            {
                for(auto& folder: this -> folders)
                {
                    if(folder -> vfs_name == folder_name)
                    {
                        std::cerr << "mkdir: cannot create directory '"
                            << folder_name << "': File exists" << std::endl;
                        return nullptr;
                    }
                }
            }

            // Create a new folder pointer
            vfs* new_folder = new vfs;
            // push it to the current list of folders
            this -> folders.push_back(new_folder);
            // set folder name for new folder 
            new_folder -> vfs_name = folder_name;
            // set parent directory
            new_folder -> parent_folder = this;

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

        // 'ls' command with hidden on
        void show_hidden_content()
        {
            std::cout << ".\n..\n";
            if(!this -> hidden_folders.empty())
            {
                for(auto& folder: this -> hidden_folders)
                    std::cout << folder -> vfs_name << std::endl;    
            }
            if(!this -> folders.empty())
            {
                for(auto& folder: this -> folders)
                    std::cout << folder -> vfs_name << std::endl;
            }
            if(!this -> hidden_file.empty())
            {
                for(auto& file_name: this -> hidden_file)
                    std::cout << file_name -> get_file_name() << std::endl;
            }
            if(!this -> file.empty())
            {
                for(auto& file_name: this -> file)
                    std::cout << file_name -> get_file_name() << std::endl;
            }
        }

        // 'ls' command with list on
        void show_list_content()
        {
            if(!this -> folders.empty())
            {
                for(auto& folder: this -> folders)
                    std::cout << "user user " << folder -> vfs_name << std::endl;
            }
            if(!this -> file.empty())
            {
                for(auto& file_name: this -> file)
                    std::cout << "user user " << file_name -> get_file_name() << std::endl;
            }
        }

        // 'ls' command with hidden and list on
        void show_hidden_list_content()
        {
            std::cout << "user user .\nuser user ..\n";
            if(!this -> hidden_folders.empty())
            {
                for(auto& folder: this -> hidden_folders)
                    std::cout << "user user " << folder -> vfs_name << std::endl;    
            }
            if(!this -> folders.empty())
            {
                for(auto& folder: this -> folders)
                    std::cout << "user user " << folder -> vfs_name << std::endl;
            }
            if(!this -> hidden_file.empty())
            {
                for(auto& file_name: this -> hidden_file)
                    std::cout << "user user " << file_name -> get_file_name() << std::endl;
            }
            if(!this -> file.empty())
            {
                for(auto& file_name: this -> file)
                    std::cout << "user user " << file_name -> get_file_name() << std::endl;
            }
        }

        // Go to folder
        vfs* go_to(std::string args, bool return_for_mkdir = false)
        {
            vfs* go_to_folder = this;
            std::vector<std::string> folder_list;
            folder_list = 
                    boost::split(folder_list, args, boost::is_any_of("/"));

            // We do not care if the last element was an empty string.
            // Popping this element will eliminate any unexpected results
            auto it = folder_list.end() - 1;
            if(*it == "")
                folder_list.pop_back();

            if(folder_list.size() == 1 && return_for_mkdir)
                return this;

            for(auto&& folder_name: folder_list)
            {

                if(folder_name == this -> folder_alias)
                {
                    // Get back to same folder
                    continue;

                } else if(folder_name == this -> parent_folder_alias)
                {
                    // Go to parent folder
                    vfs* temp = go_to_folder;
                    temp = go_to_folder -> move_up();
                    if(temp == nullptr)
                    {
                        // Trying to go above root of our directory.
                        std::cerr << "Cannot determine the location"
                            " to place the directory." << std::endl;
                    } else
                        go_to_folder = temp;

                } else
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
            }

            return go_to_folder;
        }

        // Go to folder containing file
        std::tuple<vfs*, std::string> go_to_file(std::string args)
        {
            vfs* go_to_folder = this;
            std::vector<std::string> folder_list;
            folder_list = 
                    boost::split(folder_list, args, boost::is_any_of("/"));

            // We do not care if the last element was an empty string.
            // Popping this element will eliminate any unexpected results
            auto it = folder_list.end() - 1;
            if(*it == "")
                folder_list.pop_back();

            it = folder_list.end() - 1;

            // Store file name to send it as a tuple
            std::string file_name = (*it);

            // Send a tuple with folder address and file name
            if(folder_list.size() == 1 && (*it) != "." && (*it) != "..")
                return std::make_tuple(this, file_name);

            // Pops the file name from the list
            folder_list.pop_back();

            for(auto&& folder_name: folder_list)
            {

                if(folder_name == this -> folder_alias)
                {
                    // Get back to same folder
                    continue;

                } else if(folder_name == this -> parent_folder_alias)
                {
                    // Go to parent folder
                    vfs* temp = go_to_folder;
                    temp = go_to_folder -> move_up();
                    if(temp == nullptr)
                    {
                        // Trying to go above root of our directory.
                        std::cerr << "Cannot determine the location"
                            " to place the directory." << std::endl;
                    } else
                        go_to_folder = temp;

                } else
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
                        return std::make_tuple(nullptr, file_name);
                    }
                }
            }

            return std::make_tuple(go_to_folder, file_name);
        }

        // Is folder
        bool is_folder(std::string name)
        {
            if(name == "." || name == "..")
                return false;
            
            // check if folder name matches with file name
            for(auto& folder: this -> folders)
            {
                if(folder -> vfs_name == name)
                    return true;
            }

            // folder name didn't match
            return false;
        }

        // File status
        std::tuple<vfms::file*, bool> get_file(std::string file_name)
        {
            for(auto& name: this -> file)
            {
                if(name -> get_file_name() == file_name)
                    return std::make_tuple(name, true);
            }
            return std::make_tuple(nullptr, false);
        }

        // Add file
        void add_file(vfms::file* new_file)
        {
            this -> file.push_back(new_file);
        }
    };
}

#endif /* FILE_STRUCTURE_HPP */
