#ifndef FILE_STRUCTURE_HPP
#define FILE_STRUCTURE_HPP

#include <vector>
#include <iostream>

namespace vfms
{
    class file
    {
        // file name
        std::string file_name;
        // file content. We assume that we get a vector of paragraphs.
        std::vector<std::string> file_content;


    public:

        // Fill in the file with the content added by the user.
        file* create_file(std::vector<std::string> content)
        {
            // Iterating over every paragraph
            for(auto&& element: content)
            {
                this -> file_content.push_back(element);
            }
            return this;
        }
    };

    class vfs
    {
        // folder will be of the type vfs
        std::vector<vfms::vfs> folder;
        // folder name for the current vfs
        std::string vfs_name;
        // a folder can contain files as well
        std::vector<vfms::file> file;         


    public:
        vfs* create_folder(std::string folder_name)
        {
            vfs* new_folder = new vfs;
            new_folder -> vfs_name = folder_name;

            return new_folder;
        }

        void remove_folder(std::string folder_name)
        {
            auto it = this -> folder.begin();
            while(it != this -> folder.end())
            {
                if((*it).vfs_name == folder_name)
                    it = folder.erase(it);
                else
                    ++it;
            }
        }
    };
}

#endif /* FILE_STRUCTURE_HPP */