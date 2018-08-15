#include <iostream>
#include <vector>

#include "../VFMS/file.hpp"

namespace vfms
{
    // Set file name
    void file::set_file_name(std::string& file_name)
    {
        this -> file_name = file_name;
    }

    // Get file name
    std::string file::get_file_name()
    {
        return this -> file_name;
    }

    // Fill in the file with the content added by the user.
    file* file::create_file(std::vector<std::string> content)
    {
        // Iterating over every paragraph
        for(auto&& element: content)
        {
            this -> file_content.push_back(element);
        }
        return this;
    }

    // Print out the content of the file.
    void file::print_file_content()
    {
        for(auto&& element: this -> file_content)
        {
            std::cout << element << std::endl;
        }
    }
}
    