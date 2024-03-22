# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/kirito/projects/mprpc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kirito/projects/mprpc/cmake/build

# Include any dependencies generated for this target.
include src/CMakeFiles/mprpc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/mprpc.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/mprpc.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/mprpc.dir/flags.make

src/CMakeFiles/mprpc.dir/mprpcapplication.cpp.o: src/CMakeFiles/mprpc.dir/flags.make
src/CMakeFiles/mprpc.dir/mprpcapplication.cpp.o: ../../src/mprpcapplication.cpp
src/CMakeFiles/mprpc.dir/mprpcapplication.cpp.o: src/CMakeFiles/mprpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kirito/projects/mprpc/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/mprpc.dir/mprpcapplication.cpp.o"
	cd /home/kirito/projects/mprpc/cmake/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/mprpc.dir/mprpcapplication.cpp.o -MF CMakeFiles/mprpc.dir/mprpcapplication.cpp.o.d -o CMakeFiles/mprpc.dir/mprpcapplication.cpp.o -c /home/kirito/projects/mprpc/src/mprpcapplication.cpp

src/CMakeFiles/mprpc.dir/mprpcapplication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mprpc.dir/mprpcapplication.cpp.i"
	cd /home/kirito/projects/mprpc/cmake/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kirito/projects/mprpc/src/mprpcapplication.cpp > CMakeFiles/mprpc.dir/mprpcapplication.cpp.i

src/CMakeFiles/mprpc.dir/mprpcapplication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mprpc.dir/mprpcapplication.cpp.s"
	cd /home/kirito/projects/mprpc/cmake/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kirito/projects/mprpc/src/mprpcapplication.cpp -o CMakeFiles/mprpc.dir/mprpcapplication.cpp.s

src/CMakeFiles/mprpc.dir/rpcprovider.cpp.o: src/CMakeFiles/mprpc.dir/flags.make
src/CMakeFiles/mprpc.dir/rpcprovider.cpp.o: ../../src/rpcprovider.cpp
src/CMakeFiles/mprpc.dir/rpcprovider.cpp.o: src/CMakeFiles/mprpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kirito/projects/mprpc/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/mprpc.dir/rpcprovider.cpp.o"
	cd /home/kirito/projects/mprpc/cmake/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/mprpc.dir/rpcprovider.cpp.o -MF CMakeFiles/mprpc.dir/rpcprovider.cpp.o.d -o CMakeFiles/mprpc.dir/rpcprovider.cpp.o -c /home/kirito/projects/mprpc/src/rpcprovider.cpp

src/CMakeFiles/mprpc.dir/rpcprovider.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mprpc.dir/rpcprovider.cpp.i"
	cd /home/kirito/projects/mprpc/cmake/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kirito/projects/mprpc/src/rpcprovider.cpp > CMakeFiles/mprpc.dir/rpcprovider.cpp.i

src/CMakeFiles/mprpc.dir/rpcprovider.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mprpc.dir/rpcprovider.cpp.s"
	cd /home/kirito/projects/mprpc/cmake/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kirito/projects/mprpc/src/rpcprovider.cpp -o CMakeFiles/mprpc.dir/rpcprovider.cpp.s

# Object files for target mprpc
mprpc_OBJECTS = \
"CMakeFiles/mprpc.dir/mprpcapplication.cpp.o" \
"CMakeFiles/mprpc.dir/rpcprovider.cpp.o"

# External object files for target mprpc
mprpc_EXTERNAL_OBJECTS =

../../lib/libmprpc.so: src/CMakeFiles/mprpc.dir/mprpcapplication.cpp.o
../../lib/libmprpc.so: src/CMakeFiles/mprpc.dir/rpcprovider.cpp.o
../../lib/libmprpc.so: src/CMakeFiles/mprpc.dir/build.make
../../lib/libmprpc.so: src/CMakeFiles/mprpc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kirito/projects/mprpc/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library ../../../lib/libmprpc.so"
	cd /home/kirito/projects/mprpc/cmake/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mprpc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/mprpc.dir/build: ../../lib/libmprpc.so
.PHONY : src/CMakeFiles/mprpc.dir/build

src/CMakeFiles/mprpc.dir/clean:
	cd /home/kirito/projects/mprpc/cmake/build/src && $(CMAKE_COMMAND) -P CMakeFiles/mprpc.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/mprpc.dir/clean

src/CMakeFiles/mprpc.dir/depend:
	cd /home/kirito/projects/mprpc/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kirito/projects/mprpc /home/kirito/projects/mprpc/src /home/kirito/projects/mprpc/cmake/build /home/kirito/projects/mprpc/cmake/build/src /home/kirito/projects/mprpc/cmake/build/src/CMakeFiles/mprpc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/mprpc.dir/depend

