# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zjh/Linux_demo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zjh/Linux_demo/build

# Include any dependencies generated for this target.
include CMakeFiles/copyzip.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/copyzip.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/copyzip.dir/flags.make

CMakeFiles/copyzip.dir/src/copyzip.cpp.o: CMakeFiles/copyzip.dir/flags.make
CMakeFiles/copyzip.dir/src/copyzip.cpp.o: ../src/copyzip.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zjh/Linux_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/copyzip.dir/src/copyzip.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/copyzip.dir/src/copyzip.cpp.o -c /home/zjh/Linux_demo/src/copyzip.cpp

CMakeFiles/copyzip.dir/src/copyzip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/copyzip.dir/src/copyzip.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zjh/Linux_demo/src/copyzip.cpp > CMakeFiles/copyzip.dir/src/copyzip.cpp.i

CMakeFiles/copyzip.dir/src/copyzip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/copyzip.dir/src/copyzip.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zjh/Linux_demo/src/copyzip.cpp -o CMakeFiles/copyzip.dir/src/copyzip.cpp.s

# Object files for target copyzip
copyzip_OBJECTS = \
"CMakeFiles/copyzip.dir/src/copyzip.cpp.o"

# External object files for target copyzip
copyzip_EXTERNAL_OBJECTS =

../bin/copyzip: CMakeFiles/copyzip.dir/src/copyzip.cpp.o
../bin/copyzip: CMakeFiles/copyzip.dir/build.make
../bin/copyzip: /usr/lib/x86_64-linux-gnu/libz.so
../bin/copyzip: /usr/lib/x86_64-linux-gnu/libzip.so
../bin/copyzip: CMakeFiles/copyzip.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zjh/Linux_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/copyzip"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/copyzip.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/copyzip.dir/build: ../bin/copyzip

.PHONY : CMakeFiles/copyzip.dir/build

CMakeFiles/copyzip.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/copyzip.dir/cmake_clean.cmake
.PHONY : CMakeFiles/copyzip.dir/clean

CMakeFiles/copyzip.dir/depend:
	cd /home/zjh/Linux_demo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zjh/Linux_demo /home/zjh/Linux_demo /home/zjh/Linux_demo/build /home/zjh/Linux_demo/build /home/zjh/Linux_demo/build/CMakeFiles/copyzip.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/copyzip.dir/depend

