all: vfms

CFLAGS_DYNAMIC = -shared -fPIC
INCLUDE_DIR = -I/home/nk/projects/VFMS
LINK_DIR = -L/home/nk/projects/VFMS

vfms: src/main.cpp
	$(CXX) $(INCLUDE_DIR) $(LINK_DIR) -std=c++17 -l boost_system src/main.cpp -o vfms

clean: 
	rm vfms lib_vfms_component.so