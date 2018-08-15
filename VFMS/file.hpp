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

        // Set file name
        void set_file_name(std::string& file_name);

        // Get file name
        std::string get_file_name();

        // Fill in the file with the content added by the user.
        file* create_file(std::vector<std::string> content);

        // Print out the content of the file.
        void print_file_content();
    };
}

#endif /* FILE_HPP */
