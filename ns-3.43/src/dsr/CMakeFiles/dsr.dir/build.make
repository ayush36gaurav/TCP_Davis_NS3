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
include src/dsr/CMakeFiles/dsr.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/dsr/CMakeFiles/dsr.dir/compiler_depend.make

# Include the progress variables for this target.
include src/dsr/CMakeFiles/dsr.dir/progress.make

# Include the compile flags for this target's objects.
include src/dsr/CMakeFiles/dsr.dir/flags.make

src/dsr/CMakeFiles/dsr.dir/helper/dsr-helper.cc.o: src/dsr/CMakeFiles/dsr.dir/flags.make
src/dsr/CMakeFiles/dsr.dir/helper/dsr-helper.cc.o: src/dsr/helper/dsr-helper.cc
src/dsr/CMakeFiles/dsr.dir/helper/dsr-helper.cc.o: src/dsr/CMakeFiles/dsr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/dsr/CMakeFiles/dsr.dir/helper/dsr-helper.cc.o"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/dsr/CMakeFiles/dsr.dir/helper/dsr-helper.cc.o -MF CMakeFiles/dsr.dir/helper/dsr-helper.cc.o.d -o CMakeFiles/dsr.dir/helper/dsr-helper.cc.o -c /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/helper/dsr-helper.cc

src/dsr/CMakeFiles/dsr.dir/helper/dsr-helper.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dsr.dir/helper/dsr-helper.cc.i"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/helper/dsr-helper.cc > CMakeFiles/dsr.dir/helper/dsr-helper.cc.i

src/dsr/CMakeFiles/dsr.dir/helper/dsr-helper.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dsr.dir/helper/dsr-helper.cc.s"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/helper/dsr-helper.cc -o CMakeFiles/dsr.dir/helper/dsr-helper.cc.s

src/dsr/CMakeFiles/dsr.dir/helper/dsr-main-helper.cc.o: src/dsr/CMakeFiles/dsr.dir/flags.make
src/dsr/CMakeFiles/dsr.dir/helper/dsr-main-helper.cc.o: src/dsr/helper/dsr-main-helper.cc
src/dsr/CMakeFiles/dsr.dir/helper/dsr-main-helper.cc.o: src/dsr/CMakeFiles/dsr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/dsr/CMakeFiles/dsr.dir/helper/dsr-main-helper.cc.o"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/dsr/CMakeFiles/dsr.dir/helper/dsr-main-helper.cc.o -MF CMakeFiles/dsr.dir/helper/dsr-main-helper.cc.o.d -o CMakeFiles/dsr.dir/helper/dsr-main-helper.cc.o -c /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/helper/dsr-main-helper.cc

src/dsr/CMakeFiles/dsr.dir/helper/dsr-main-helper.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dsr.dir/helper/dsr-main-helper.cc.i"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/helper/dsr-main-helper.cc > CMakeFiles/dsr.dir/helper/dsr-main-helper.cc.i

src/dsr/CMakeFiles/dsr.dir/helper/dsr-main-helper.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dsr.dir/helper/dsr-main-helper.cc.s"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/helper/dsr-main-helper.cc -o CMakeFiles/dsr.dir/helper/dsr-main-helper.cc.s

src/dsr/CMakeFiles/dsr.dir/model/dsr-errorbuff.cc.o: src/dsr/CMakeFiles/dsr.dir/flags.make
src/dsr/CMakeFiles/dsr.dir/model/dsr-errorbuff.cc.o: src/dsr/model/dsr-errorbuff.cc
src/dsr/CMakeFiles/dsr.dir/model/dsr-errorbuff.cc.o: src/dsr/CMakeFiles/dsr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/dsr/CMakeFiles/dsr.dir/model/dsr-errorbuff.cc.o"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/dsr/CMakeFiles/dsr.dir/model/dsr-errorbuff.cc.o -MF CMakeFiles/dsr.dir/model/dsr-errorbuff.cc.o.d -o CMakeFiles/dsr.dir/model/dsr-errorbuff.cc.o -c /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-errorbuff.cc

src/dsr/CMakeFiles/dsr.dir/model/dsr-errorbuff.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dsr.dir/model/dsr-errorbuff.cc.i"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-errorbuff.cc > CMakeFiles/dsr.dir/model/dsr-errorbuff.cc.i

src/dsr/CMakeFiles/dsr.dir/model/dsr-errorbuff.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dsr.dir/model/dsr-errorbuff.cc.s"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-errorbuff.cc -o CMakeFiles/dsr.dir/model/dsr-errorbuff.cc.s

src/dsr/CMakeFiles/dsr.dir/model/dsr-fs-header.cc.o: src/dsr/CMakeFiles/dsr.dir/flags.make
src/dsr/CMakeFiles/dsr.dir/model/dsr-fs-header.cc.o: src/dsr/model/dsr-fs-header.cc
src/dsr/CMakeFiles/dsr.dir/model/dsr-fs-header.cc.o: src/dsr/CMakeFiles/dsr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/dsr/CMakeFiles/dsr.dir/model/dsr-fs-header.cc.o"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/dsr/CMakeFiles/dsr.dir/model/dsr-fs-header.cc.o -MF CMakeFiles/dsr.dir/model/dsr-fs-header.cc.o.d -o CMakeFiles/dsr.dir/model/dsr-fs-header.cc.o -c /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-fs-header.cc

src/dsr/CMakeFiles/dsr.dir/model/dsr-fs-header.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dsr.dir/model/dsr-fs-header.cc.i"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-fs-header.cc > CMakeFiles/dsr.dir/model/dsr-fs-header.cc.i

src/dsr/CMakeFiles/dsr.dir/model/dsr-fs-header.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dsr.dir/model/dsr-fs-header.cc.s"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-fs-header.cc -o CMakeFiles/dsr.dir/model/dsr-fs-header.cc.s

src/dsr/CMakeFiles/dsr.dir/model/dsr-gratuitous-reply-table.cc.o: src/dsr/CMakeFiles/dsr.dir/flags.make
src/dsr/CMakeFiles/dsr.dir/model/dsr-gratuitous-reply-table.cc.o: src/dsr/model/dsr-gratuitous-reply-table.cc
src/dsr/CMakeFiles/dsr.dir/model/dsr-gratuitous-reply-table.cc.o: src/dsr/CMakeFiles/dsr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/dsr/CMakeFiles/dsr.dir/model/dsr-gratuitous-reply-table.cc.o"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/dsr/CMakeFiles/dsr.dir/model/dsr-gratuitous-reply-table.cc.o -MF CMakeFiles/dsr.dir/model/dsr-gratuitous-reply-table.cc.o.d -o CMakeFiles/dsr.dir/model/dsr-gratuitous-reply-table.cc.o -c /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-gratuitous-reply-table.cc

src/dsr/CMakeFiles/dsr.dir/model/dsr-gratuitous-reply-table.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dsr.dir/model/dsr-gratuitous-reply-table.cc.i"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-gratuitous-reply-table.cc > CMakeFiles/dsr.dir/model/dsr-gratuitous-reply-table.cc.i

src/dsr/CMakeFiles/dsr.dir/model/dsr-gratuitous-reply-table.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dsr.dir/model/dsr-gratuitous-reply-table.cc.s"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-gratuitous-reply-table.cc -o CMakeFiles/dsr.dir/model/dsr-gratuitous-reply-table.cc.s

src/dsr/CMakeFiles/dsr.dir/model/dsr-maintain-buff.cc.o: src/dsr/CMakeFiles/dsr.dir/flags.make
src/dsr/CMakeFiles/dsr.dir/model/dsr-maintain-buff.cc.o: src/dsr/model/dsr-maintain-buff.cc
src/dsr/CMakeFiles/dsr.dir/model/dsr-maintain-buff.cc.o: src/dsr/CMakeFiles/dsr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/dsr/CMakeFiles/dsr.dir/model/dsr-maintain-buff.cc.o"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/dsr/CMakeFiles/dsr.dir/model/dsr-maintain-buff.cc.o -MF CMakeFiles/dsr.dir/model/dsr-maintain-buff.cc.o.d -o CMakeFiles/dsr.dir/model/dsr-maintain-buff.cc.o -c /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-maintain-buff.cc

src/dsr/CMakeFiles/dsr.dir/model/dsr-maintain-buff.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dsr.dir/model/dsr-maintain-buff.cc.i"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-maintain-buff.cc > CMakeFiles/dsr.dir/model/dsr-maintain-buff.cc.i

src/dsr/CMakeFiles/dsr.dir/model/dsr-maintain-buff.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dsr.dir/model/dsr-maintain-buff.cc.s"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-maintain-buff.cc -o CMakeFiles/dsr.dir/model/dsr-maintain-buff.cc.s

src/dsr/CMakeFiles/dsr.dir/model/dsr-network-queue.cc.o: src/dsr/CMakeFiles/dsr.dir/flags.make
src/dsr/CMakeFiles/dsr.dir/model/dsr-network-queue.cc.o: src/dsr/model/dsr-network-queue.cc
src/dsr/CMakeFiles/dsr.dir/model/dsr-network-queue.cc.o: src/dsr/CMakeFiles/dsr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/dsr/CMakeFiles/dsr.dir/model/dsr-network-queue.cc.o"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/dsr/CMakeFiles/dsr.dir/model/dsr-network-queue.cc.o -MF CMakeFiles/dsr.dir/model/dsr-network-queue.cc.o.d -o CMakeFiles/dsr.dir/model/dsr-network-queue.cc.o -c /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-network-queue.cc

src/dsr/CMakeFiles/dsr.dir/model/dsr-network-queue.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dsr.dir/model/dsr-network-queue.cc.i"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-network-queue.cc > CMakeFiles/dsr.dir/model/dsr-network-queue.cc.i

src/dsr/CMakeFiles/dsr.dir/model/dsr-network-queue.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dsr.dir/model/dsr-network-queue.cc.s"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-network-queue.cc -o CMakeFiles/dsr.dir/model/dsr-network-queue.cc.s

src/dsr/CMakeFiles/dsr.dir/model/dsr-option-header.cc.o: src/dsr/CMakeFiles/dsr.dir/flags.make
src/dsr/CMakeFiles/dsr.dir/model/dsr-option-header.cc.o: src/dsr/model/dsr-option-header.cc
src/dsr/CMakeFiles/dsr.dir/model/dsr-option-header.cc.o: src/dsr/CMakeFiles/dsr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/dsr/CMakeFiles/dsr.dir/model/dsr-option-header.cc.o"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/dsr/CMakeFiles/dsr.dir/model/dsr-option-header.cc.o -MF CMakeFiles/dsr.dir/model/dsr-option-header.cc.o.d -o CMakeFiles/dsr.dir/model/dsr-option-header.cc.o -c /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-option-header.cc

src/dsr/CMakeFiles/dsr.dir/model/dsr-option-header.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dsr.dir/model/dsr-option-header.cc.i"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-option-header.cc > CMakeFiles/dsr.dir/model/dsr-option-header.cc.i

src/dsr/CMakeFiles/dsr.dir/model/dsr-option-header.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dsr.dir/model/dsr-option-header.cc.s"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-option-header.cc -o CMakeFiles/dsr.dir/model/dsr-option-header.cc.s

src/dsr/CMakeFiles/dsr.dir/model/dsr-options.cc.o: src/dsr/CMakeFiles/dsr.dir/flags.make
src/dsr/CMakeFiles/dsr.dir/model/dsr-options.cc.o: src/dsr/model/dsr-options.cc
src/dsr/CMakeFiles/dsr.dir/model/dsr-options.cc.o: src/dsr/CMakeFiles/dsr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/dsr/CMakeFiles/dsr.dir/model/dsr-options.cc.o"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/dsr/CMakeFiles/dsr.dir/model/dsr-options.cc.o -MF CMakeFiles/dsr.dir/model/dsr-options.cc.o.d -o CMakeFiles/dsr.dir/model/dsr-options.cc.o -c /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-options.cc

src/dsr/CMakeFiles/dsr.dir/model/dsr-options.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dsr.dir/model/dsr-options.cc.i"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-options.cc > CMakeFiles/dsr.dir/model/dsr-options.cc.i

src/dsr/CMakeFiles/dsr.dir/model/dsr-options.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dsr.dir/model/dsr-options.cc.s"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-options.cc -o CMakeFiles/dsr.dir/model/dsr-options.cc.s

src/dsr/CMakeFiles/dsr.dir/model/dsr-passive-buff.cc.o: src/dsr/CMakeFiles/dsr.dir/flags.make
src/dsr/CMakeFiles/dsr.dir/model/dsr-passive-buff.cc.o: src/dsr/model/dsr-passive-buff.cc
src/dsr/CMakeFiles/dsr.dir/model/dsr-passive-buff.cc.o: src/dsr/CMakeFiles/dsr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/dsr/CMakeFiles/dsr.dir/model/dsr-passive-buff.cc.o"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/dsr/CMakeFiles/dsr.dir/model/dsr-passive-buff.cc.o -MF CMakeFiles/dsr.dir/model/dsr-passive-buff.cc.o.d -o CMakeFiles/dsr.dir/model/dsr-passive-buff.cc.o -c /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-passive-buff.cc

src/dsr/CMakeFiles/dsr.dir/model/dsr-passive-buff.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dsr.dir/model/dsr-passive-buff.cc.i"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-passive-buff.cc > CMakeFiles/dsr.dir/model/dsr-passive-buff.cc.i

src/dsr/CMakeFiles/dsr.dir/model/dsr-passive-buff.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dsr.dir/model/dsr-passive-buff.cc.s"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-passive-buff.cc -o CMakeFiles/dsr.dir/model/dsr-passive-buff.cc.s

src/dsr/CMakeFiles/dsr.dir/model/dsr-rcache.cc.o: src/dsr/CMakeFiles/dsr.dir/flags.make
src/dsr/CMakeFiles/dsr.dir/model/dsr-rcache.cc.o: src/dsr/model/dsr-rcache.cc
src/dsr/CMakeFiles/dsr.dir/model/dsr-rcache.cc.o: src/dsr/CMakeFiles/dsr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object src/dsr/CMakeFiles/dsr.dir/model/dsr-rcache.cc.o"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/dsr/CMakeFiles/dsr.dir/model/dsr-rcache.cc.o -MF CMakeFiles/dsr.dir/model/dsr-rcache.cc.o.d -o CMakeFiles/dsr.dir/model/dsr-rcache.cc.o -c /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-rcache.cc

src/dsr/CMakeFiles/dsr.dir/model/dsr-rcache.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dsr.dir/model/dsr-rcache.cc.i"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-rcache.cc > CMakeFiles/dsr.dir/model/dsr-rcache.cc.i

src/dsr/CMakeFiles/dsr.dir/model/dsr-rcache.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dsr.dir/model/dsr-rcache.cc.s"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-rcache.cc -o CMakeFiles/dsr.dir/model/dsr-rcache.cc.s

src/dsr/CMakeFiles/dsr.dir/model/dsr-routing.cc.o: src/dsr/CMakeFiles/dsr.dir/flags.make
src/dsr/CMakeFiles/dsr.dir/model/dsr-routing.cc.o: src/dsr/model/dsr-routing.cc
src/dsr/CMakeFiles/dsr.dir/model/dsr-routing.cc.o: src/dsr/CMakeFiles/dsr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object src/dsr/CMakeFiles/dsr.dir/model/dsr-routing.cc.o"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/dsr/CMakeFiles/dsr.dir/model/dsr-routing.cc.o -MF CMakeFiles/dsr.dir/model/dsr-routing.cc.o.d -o CMakeFiles/dsr.dir/model/dsr-routing.cc.o -c /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-routing.cc

src/dsr/CMakeFiles/dsr.dir/model/dsr-routing.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dsr.dir/model/dsr-routing.cc.i"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-routing.cc > CMakeFiles/dsr.dir/model/dsr-routing.cc.i

src/dsr/CMakeFiles/dsr.dir/model/dsr-routing.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dsr.dir/model/dsr-routing.cc.s"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-routing.cc -o CMakeFiles/dsr.dir/model/dsr-routing.cc.s

src/dsr/CMakeFiles/dsr.dir/model/dsr-rreq-table.cc.o: src/dsr/CMakeFiles/dsr.dir/flags.make
src/dsr/CMakeFiles/dsr.dir/model/dsr-rreq-table.cc.o: src/dsr/model/dsr-rreq-table.cc
src/dsr/CMakeFiles/dsr.dir/model/dsr-rreq-table.cc.o: src/dsr/CMakeFiles/dsr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object src/dsr/CMakeFiles/dsr.dir/model/dsr-rreq-table.cc.o"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/dsr/CMakeFiles/dsr.dir/model/dsr-rreq-table.cc.o -MF CMakeFiles/dsr.dir/model/dsr-rreq-table.cc.o.d -o CMakeFiles/dsr.dir/model/dsr-rreq-table.cc.o -c /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-rreq-table.cc

src/dsr/CMakeFiles/dsr.dir/model/dsr-rreq-table.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dsr.dir/model/dsr-rreq-table.cc.i"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-rreq-table.cc > CMakeFiles/dsr.dir/model/dsr-rreq-table.cc.i

src/dsr/CMakeFiles/dsr.dir/model/dsr-rreq-table.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dsr.dir/model/dsr-rreq-table.cc.s"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-rreq-table.cc -o CMakeFiles/dsr.dir/model/dsr-rreq-table.cc.s

src/dsr/CMakeFiles/dsr.dir/model/dsr-rsendbuff.cc.o: src/dsr/CMakeFiles/dsr.dir/flags.make
src/dsr/CMakeFiles/dsr.dir/model/dsr-rsendbuff.cc.o: src/dsr/model/dsr-rsendbuff.cc
src/dsr/CMakeFiles/dsr.dir/model/dsr-rsendbuff.cc.o: src/dsr/CMakeFiles/dsr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object src/dsr/CMakeFiles/dsr.dir/model/dsr-rsendbuff.cc.o"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/dsr/CMakeFiles/dsr.dir/model/dsr-rsendbuff.cc.o -MF CMakeFiles/dsr.dir/model/dsr-rsendbuff.cc.o.d -o CMakeFiles/dsr.dir/model/dsr-rsendbuff.cc.o -c /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-rsendbuff.cc

src/dsr/CMakeFiles/dsr.dir/model/dsr-rsendbuff.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/dsr.dir/model/dsr-rsendbuff.cc.i"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-rsendbuff.cc > CMakeFiles/dsr.dir/model/dsr-rsendbuff.cc.i

src/dsr/CMakeFiles/dsr.dir/model/dsr-rsendbuff.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/dsr.dir/model/dsr-rsendbuff.cc.s"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/model/dsr-rsendbuff.cc -o CMakeFiles/dsr.dir/model/dsr-rsendbuff.cc.s

# Object files for target dsr
dsr_OBJECTS = \
"CMakeFiles/dsr.dir/helper/dsr-helper.cc.o" \
"CMakeFiles/dsr.dir/helper/dsr-main-helper.cc.o" \
"CMakeFiles/dsr.dir/model/dsr-errorbuff.cc.o" \
"CMakeFiles/dsr.dir/model/dsr-fs-header.cc.o" \
"CMakeFiles/dsr.dir/model/dsr-gratuitous-reply-table.cc.o" \
"CMakeFiles/dsr.dir/model/dsr-maintain-buff.cc.o" \
"CMakeFiles/dsr.dir/model/dsr-network-queue.cc.o" \
"CMakeFiles/dsr.dir/model/dsr-option-header.cc.o" \
"CMakeFiles/dsr.dir/model/dsr-options.cc.o" \
"CMakeFiles/dsr.dir/model/dsr-passive-buff.cc.o" \
"CMakeFiles/dsr.dir/model/dsr-rcache.cc.o" \
"CMakeFiles/dsr.dir/model/dsr-routing.cc.o" \
"CMakeFiles/dsr.dir/model/dsr-rreq-table.cc.o" \
"CMakeFiles/dsr.dir/model/dsr-rsendbuff.cc.o"

# External object files for target dsr
dsr_EXTERNAL_OBJECTS =

build/lib/libns3.43-dsr-debug.so: src/dsr/CMakeFiles/dsr.dir/helper/dsr-helper.cc.o
build/lib/libns3.43-dsr-debug.so: src/dsr/CMakeFiles/dsr.dir/helper/dsr-main-helper.cc.o
build/lib/libns3.43-dsr-debug.so: src/dsr/CMakeFiles/dsr.dir/model/dsr-errorbuff.cc.o
build/lib/libns3.43-dsr-debug.so: src/dsr/CMakeFiles/dsr.dir/model/dsr-fs-header.cc.o
build/lib/libns3.43-dsr-debug.so: src/dsr/CMakeFiles/dsr.dir/model/dsr-gratuitous-reply-table.cc.o
build/lib/libns3.43-dsr-debug.so: src/dsr/CMakeFiles/dsr.dir/model/dsr-maintain-buff.cc.o
build/lib/libns3.43-dsr-debug.so: src/dsr/CMakeFiles/dsr.dir/model/dsr-network-queue.cc.o
build/lib/libns3.43-dsr-debug.so: src/dsr/CMakeFiles/dsr.dir/model/dsr-option-header.cc.o
build/lib/libns3.43-dsr-debug.so: src/dsr/CMakeFiles/dsr.dir/model/dsr-options.cc.o
build/lib/libns3.43-dsr-debug.so: src/dsr/CMakeFiles/dsr.dir/model/dsr-passive-buff.cc.o
build/lib/libns3.43-dsr-debug.so: src/dsr/CMakeFiles/dsr.dir/model/dsr-rcache.cc.o
build/lib/libns3.43-dsr-debug.so: src/dsr/CMakeFiles/dsr.dir/model/dsr-routing.cc.o
build/lib/libns3.43-dsr-debug.so: src/dsr/CMakeFiles/dsr.dir/model/dsr-rreq-table.cc.o
build/lib/libns3.43-dsr-debug.so: src/dsr/CMakeFiles/dsr.dir/model/dsr-rsendbuff.cc.o
build/lib/libns3.43-dsr-debug.so: src/dsr/CMakeFiles/dsr.dir/build.make
build/lib/libns3.43-dsr-debug.so: /usr/lib/x86_64-linux-gnu/libgsl.so
build/lib/libns3.43-dsr-debug.so: /usr/lib/x86_64-linux-gnu/libgslcblas.so
build/lib/libns3.43-dsr-debug.so: /usr/lib/x86_64-linux-gnu/libsqlite3.so
build/lib/libns3.43-dsr-debug.so: src/dsr/CMakeFiles/dsr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX shared library ../../build/lib/libns3.43-dsr-debug.so"
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dsr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/dsr/CMakeFiles/dsr.dir/build: build/lib/libns3.43-dsr-debug.so
.PHONY : src/dsr/CMakeFiles/dsr.dir/build

src/dsr/CMakeFiles/dsr.dir/clean:
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr && $(CMAKE_COMMAND) -P CMakeFiles/dsr.dir/cmake_clean.cmake
.PHONY : src/dsr/CMakeFiles/dsr.dir/clean

src/dsr/CMakeFiles/dsr.dir/depend:
	cd /home/ayush-gaurav/ns-allinone-3.43/ns-3.43 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ayush-gaurav/ns-allinone-3.43/ns-3.43 /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr /home/ayush-gaurav/ns-allinone-3.43/ns-3.43 /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/CMakeFiles/dsr.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/dsr/CMakeFiles/dsr.dir/depend

