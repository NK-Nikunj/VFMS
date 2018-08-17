#include <iostream>

namespace vfms
{
    namespace assets
    {
        void send_error(std::string error_for)
        {
            std::cerr << error_for << ": can not interpret options for the given command.\n";
            return;
        }
    }
}