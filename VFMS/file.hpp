#ifndef FILE_HPP
#define FILE_HPP

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

        // Print out the content of the file.
        void print_file_content()
        {
            for(auto&& element: this -> file_content)
            {
                std::cout << element << std::endl;
            }
        }
    };
}

#endif /* FILE_HPP */