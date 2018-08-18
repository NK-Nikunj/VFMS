#include <iostream>

namespace vfms
{
    namespace assets
    {
        void usage(std::string use_for)
        {
            std::cout << "Try ' "<< use_for << " help'for more information.\n";
            return;
        }
    }
}