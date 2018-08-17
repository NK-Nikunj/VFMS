#ifndef LS_HPP
#define LS_HPP

namespace vfms
{
    namespace command
    {
        // Currently we support only long list and hidden file formats
        enum ls_options_short
        {
            l,
            a,
        };

        // Currently we support only show all files and help formats
        enum ls_options_long
        {
            help,
            all
        };
    }
}

#endif /* LS_HPP */