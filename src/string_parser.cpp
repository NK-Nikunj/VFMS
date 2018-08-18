#include <vector>
#include <iostream>

// Includes all necessary
#include <VFMS/command_map.hpp>
#include <VFMS/file.hpp>
#include <VFMS/vfs.hpp>
#include <VFMS/string_parser.hpp>

namespace vfms
{
    extern std::unordered_map<std::string, commands> valid_commands;
    extern void exec_ls(std::vector<std::string> args, vfs* current_folder);

    string_parser::string_parser(std::vector<std::string> arguments)
    {
        for(auto&& args: arguments)
        {
            this -> arguments.push_back(args);
        }
    }

    // Process the arguments and evaluate
    vfs* string_parser::process_args(vfs* current_folder)
    {
        // If user did not add any arguments, simply move ahead.
        if(this -> arguments.size() == 0)
        {
            return current_folder;
        }
            
        commands command_type;
        // unordered_map returns an exception if it doesn't find any element.
        try
        {
            command_type = valid_commands.at(this -> arguments[0]);
        } catch (...)
        {
            // Command could not be found in the list of valid command.
            std::cerr << this -> arguments[0] << " is not a valid command." << std::endl;
            return current_folder;
        }

        switch(command_type)
        {
            // 'ls' command shows files and folders in the current directory
            case ls:
                exec_ls(this -> arguments, current_folder);
                
                // Return back the current folder
                return current_folder;
            

            // 'mkdir' can create multiple folders at a single time
            case mkdir:
                if(this -> arguments.size() == 1)
                {
                    // Incorrect usage of mkdir. Raise an error.
                    std::cerr << "Wrong use of command 'mkdir'.\n"
                        "Usage: mkdir dir1 dir2 dir3" << std::endl;

                } else
                {
                    for(int i = 1; i != this -> arguments.size(); ++i)
                    {
                        // Move to the specified directory. If there is 
                        // none then raise alert that the folder 
                        // does not exists.
                        vfms::vfs* get_to_folder =
                            current_folder -> go_to(this -> arguments[i], true);

                        if(get_to_folder == current_folder){
                            // Make directory in the current folder
                            current_folder -> create_folder(this -> arguments[i]);
                        } else if(get_to_folder != nullptr)
                        {
                            // Make directory in a different folder
                            get_to_folder -> create_folder(this -> arguments[i]);
                        }
                    }
                }
                // Return back the current folder
                return current_folder;
            

            // 'cd' command allows to enter and leave directories
            case cd:
                if(this -> arguments.size() == 2)
                {
                    vfms::vfs* temp = current_folder;
                    temp = current_folder -> go_to(this -> arguments[1]);

                    // Only assign temp to current folder when there is no
                    // error raised.
                    if(temp != nullptr)
                        current_folder = temp;

                } else
                {
                    // Incorrect usage of cd. Raise an error.
                    std::cerr << "Wrong use of command 'cd'.\n"
                        "Usage: cd path/to/dir" << std::endl;                        
                }
                // Return back the current folder
                return current_folder;


            // 'touch' command creates a file with the given name                
            case touch:
                if(this -> arguments.size() == 1)
                {
                    std::cerr << "Wrong use of command 'touch'.\n"
                        "Usage: touch file1 file2 file3 .." << std::endl;
                } else
                {
                    for(auto args = this -> arguments.begin() + 1;
                        args != this -> arguments.end();
                        ++args)
                    {
                        vfms::vfs* temp = current_folder;
                        // Returned tuple containing the details
                        auto returned_tuple = current_folder -> go_to_file(*args);
                        // Store folder address as a temperory variable
                        temp = std::get<0>(returned_tuple);
                        // initialize file_name with returned file name
                        std::string file_name = std::get<1>(returned_tuple);

                        // check if the file name is actually a folder name
                        bool is_file_folder = current_folder -> is_folder(file_name);

                        // No error is raised when file has name 
                        // matching to directory
                        if(is_file_folder)
                            continue;
                        else
                        {
                            // No file or directory found
                            if(temp == nullptr)
                            {
                                // Raise error
                                std::cerr << "touch: cannot touch '"
                                    << *args << "': No such file or "
                                    "directory" << std::endl;
                            } else
                            {
                                // Create file and set it's name
                                vfms::file* new_file = new vfms::file;
                                new_file -> set_file_name(*args);

                                // Add file to current source tree
                                temp -> add_file(new_file);
                            }
                        }
                        
                    }
                }
                // Return back the current folder
                return current_folder;
            
            case ned:
                break;


            // 'cat' command shows content of files
            case cat:
                // Opens up a shell which shows anything written. Closes
                // on typing exit
                if(this -> arguments.size() == 1)
                {
                    std::string write_lines;
                    do
                    {
                        // Takes input of the string
                        std::getline(std::cin, write_lines);
                        // Outputs whatever is written
                        std::cout << write_lines << std::endl;

                    } while(write_lines != "quit");
                } else if(this -> arguments.size() == 2)
                {
                    vfms::vfs* temp = current_folder;
                    // Returned tuple containing the details
                    auto returned_tuple = current_folder -> go_to_file(this -> arguments[1]);
                    // Store folder address as a temperory variable
                    temp = std::get<0>(returned_tuple);
                    // initialize file_name with returned file name
                    std::string file_name = std::get<1>(returned_tuple);

                    // check if the file name is actually a folder name
                    bool is_file_folder = current_folder -> is_folder(file_name);

                    if(is_file_folder)
                    {
                        // Raise error saying file name is a directory 
                        std::cerr << "cat: " << file_name << ": Is a directory" << std::endl;
                    } else {
                        // Returns file status. Either file address and true
                        // or nullptr and false
                        auto file_status = current_folder -> get_file(file_name);

                        vfms::file* file_address = std::get<0>(file_status);
                        if(file_address)
                        {
                            file_address -> print_file_content();
                        } else
                        {
                            // The given file does not exists.
                            std::cerr << "cat: " << file_name << ": "
                                "No such file or directory" << std::endl;
                        }
                    }
                }
                // Return back the current folder
                return current_folder;
            
            case quit:
                std::exit(0);
        }
    }
}
