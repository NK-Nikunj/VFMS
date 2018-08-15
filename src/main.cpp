#include <iostream>

#include <iterator>
#include <algorithm>

#include "../VFMS/vfs.hpp"
#include "../VFMS/file.hpp"
#include "../VFMS/string_parser.hpp"


// Currently there is no support for argument analysis.
// This will be fixed in later versions of VFMS
int main(int argc, char** argv)
{
    // string given to string_parser to analyze
    std::string parsed_string;

    std::cout << "Welcome to the Virtual File Management System." 
            " Few things worth noting: \n"
            "1. Anything you do here is not exported. \n"
            "2. Do NOT create a file and save thinking it will "
            "be saved in your OS as well! It is a VIRTUAL system. \n"
            "3. Feel free to explore. In case of any errors, send a bug "
            "report to https://github.com/NK-Nikunj/VFMS/issues." << std::endl;

    vfms::vfs* root = new vfms::vfs;
    root -> set_vfs_name("root");

    while(true)
    {        
        std::cout << "virtual@user:";

        vfms::vfs* temp = root;

        std::string dir = "";
        while(temp != nullptr)
        {
            dir.append(temp -> get_folder_name());
            temp = temp -> move_up();
            dir.append("/");
        }
        std::vector<std::string> dir_list;
        dir_list = 
                    boost::split(dir_list, dir, boost::is_any_of("/"));
        std::reverse(std::begin(dir_list), std::end(dir_list));

        for(auto&& directories: dir_list)
            std::cout << directories << "/";
        
        std::cout << "$";

        std::getline(std::cin, parsed_string);

        std::vector<std::string> args;
        boost::split(args, parsed_string, boost::is_any_of(" "));

        vfms::string_parser analyze(args);
        root = analyze.process_args(root);
    }

    return 0;
}