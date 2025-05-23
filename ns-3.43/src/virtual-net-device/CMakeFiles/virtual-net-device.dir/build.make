# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ayush-gaurav/ns-allinone-3.43/ns-3.43

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ayush-gaurav/ns-allinone-3.43/ns-3.43

# Include any dependencies generated for this target.
include src/virtual-net-device/CMakeFiles/virtual-net-device.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/virtual-net-device/CMakeFiles/virtual-net-device.dir/compiler_depend.make

# Include the progress variables for this target.
include src/virtual-net-device/CMakeFiles/virtual-net-device.dir/progress.make

# Include the compile flags for this target's objects.
include src/virtual-net-device/CMakeFiles/virtual-net-device.dir/flags.make

src/virtual-net-device/CMakeFiles/virtual-net-device.dir/model/virtual-net-device.cc.o: src/virtual-net-device/CMakeFiles/virtual-net-device.dir/flags.make
src/virtual-net-device/CMakeFiles/virtual-net-device.dir/model/virtual-net-device.cc.o: src/virtual-net-device/model/virtual-net-device.cc
src/virtual-net-device/CMakeFiles/virtual-net-device.dir/model/virtual-net-device.cc.o: src/virtual-net-device/CMakeFiles/virtual-net-device.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/virtual-net-device/CMakeFiles/virtual-net-device.dir/model/virtual-net-device.cc.o"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/virtual-net-device && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/virtual-net-device/CMakeFiles/virtual-net-device.dir/model/virtual-net-device.cc.o -MF CMakeFiles/virtual-net-device.dir/model/virtual-net-device.cc.o.d -o CMakeFiles/virtual-net-device.dir/model/virtual-net-device.cc.o -c /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/virtual-net-device/model/virtual-net-device.cc

src/virtual-net-device/CMakeFiles/virtual-net-device.dir/model/virtual-net-device.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/virtual-net-device.dir/model/virtual-net-device.cc.i"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/virtual-net-device && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/virtual-net-device/model/virtual-net-device.cc > CMakeFiles/virtual-net-device.dir/model/virtual-net-device.cc.i

src/virtual-net-device/CMakeFiles/virtual-net-device.dir/model/virtual-net-device.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/virtual-net-device.dir/model/virtual-net-device.cc.s"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/virtual-net-device && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/virtual-net-device/model/virtual-net-device.cc -o CMakeFiles/virtual-net-device.dir/model/virtual-net-device.cc.s

# Object files for target virtual-net-device
virtual__net__device_OBJECTS = \
"CMakeFiles/virtual-net-device.dir/model/virtual-net-device.cc.o"

# External object files for target virtual-net-device
virtual__net__device_EXTERNAL_OBJECTS =

build/lib/libns3.43-virtual-net-device-debug.so: src/virtual-net-device/CMakeFiles/virtual-net-device.dir/model/virtual-net-device.cc.o
build/lib/libns3.43-virtual-net-device-debug.so: src/virtual-net-device/CMakeFiles/virtual-net-device.dir/build.make
build/lib/libns3.43-virtual-net-device-debug.so: /usr/lib/x86_64-linux-gnu/libgsl.so
build/lib/libns3.43-virtual-net-device-debug.so: /usr/lib/x86_64-linux-gnu/libgslcblas.so
build/lib/libns3.43-virtual-net-device-debug.so: /usr/lib/x86_64-linux-gnu/libsqlite3.so
build/lib/libns3.43-virtual-net-device-debug.so: src/virtual-net-device/CMakeFiles/virtual-net-device.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ../../build/lib/libns3.43-virtual-net-device-debug.so"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/virtual-net-device && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/virtual-net-device.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/virtual-net-device/CMakeFiles/virtual-net-device.dir/build: build/lib/libns3.43-virtual-net-device-debug.so
.PHONY : src/virtual-net-device/CMakeFiles/virtual-net-device.dir/build

src/virtual-net-device/CMakeFiles/virtual-net-device.dir/clean:
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/virtual-net-device && $(CMAKE_COMMAND) -P CMakeFiles/virtual-net-device.dir/cmake_clean.cmake
.PHONY : src/virtual-net-device/CMakeFiles/virtual-net-device.dir/clean

src/virtual-net-device/CMakeFiles/virtual-net-device.dir/depend:
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ayush-gaurav/ns-allinone-3.43/ns-3.43 /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/virtual-net-device /home/ayush-gaurav/ns-allinone-3.43/ns-3.43 /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/virtual-net-device /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/virtual-net-device/CMakeFiles/virtual-net-device.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/virtual-net-device/CMakeFiles/virtual-net-device.dir/depend

