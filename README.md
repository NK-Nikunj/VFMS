# VFMS (Short for Virtual File Management System)

VFMS is a basic simulation of the Linux terminal supporting basic commands like `ls`, `mkdir`, `touch`, `cat` etc. VFMS provides you with an executable. Anything ran/developed inside of VFMS will `NOT` be saved to the disk (We are working on exporting solutions though).

## Dependencies

VFMS depends on the following packages. We have provided commands for debian based OS as well.

```
    1. CMake (apt install cmake)
    2. Make (apt install make)
    3. Boost (simplest solution: aptitude install boost)
    4. C++ compiler (GCC/clang)
```


## Installation

Currently VFMS does not support installation. We provide a simple build to generate a vfms executable. To get the executable, write the following on the top tree of VFMS:

```
    $ mkdir build && cd build
    $ cmake ..
    $ make
```

To run the vfms executable:
```
    $ ./vfms
```