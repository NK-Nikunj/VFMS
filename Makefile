all: vfms

CFLAGS_DYNAMIC = -shared -fPIC
INCLUDE_DIR = -I/home/nk/projects/VFMS
LINK_DIR = -L/home/nk/projects/VFMS

vfms: src/main.cpp libvfms.so
	$(CXX) $(INCLUDE_DIR) $(LINK_DIR) -std=c++17 -l boost_system src/command_map.cpp src/string_parser.cpp src/main.cpp -o vfms

#libvfms.so: src/command_map.cpp src/string_parser.cpp
#	$(CXX) $(INCLUDE_DIR) $(LINK_DIR) $(CFLAGS_DYNAMIC) $^ -o $@

clean: 
	rm vfms lib_vfms_component.so