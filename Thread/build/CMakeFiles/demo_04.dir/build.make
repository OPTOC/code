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
CMAKE_SOURCE_DIR = /home/zjh/Thread

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zjh/Thread/build

# Include any dependencies generated for this target.
include CMakeFiles/demo_04.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/demo_04.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/demo_04.dir/flags.make

CMakeFiles/demo_04.dir/src/demo_04.cpp.o: CMakeFiles/demo_04.dir/flags.make
CMakeFiles/demo_04.dir/src/demo_04.cpp.o: ../src/demo_04.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zjh/Thread/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/demo_04.dir/src/demo_04.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo_04.dir/src/demo_04.cpp.o -c /home/zjh/Thread/src/demo_04.cpp

CMakeFiles/demo_04.dir/src/demo_04.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo_04.dir/src/demo_04.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zjh/Thread/src/demo_04.cpp > CMakeFiles/demo_04.dir/src/demo_04.cpp.i

CMakeFiles/demo_04.dir/src/demo_04.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo_04.dir/src/demo_04.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zjh/Thread/src/demo_04.cpp -o CMakeFiles/demo_04.dir/src/demo_04.cpp.s

# Object files for target demo_04
demo_04_OBJECTS = \
"CMakeFiles/demo_04.dir/src/demo_04.cpp.o"

# External object files for target demo_04
demo_04_EXTERNAL_OBJECTS =

../bin/demo_04: CMakeFiles/demo_04.dir/src/demo_04.cpp.o
../bin/demo_04: CMakeFiles/demo_04.dir/build.make
../bin/demo_04: CMakeFiles/demo_04.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zjh/Thread/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/demo_04"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demo_04.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/demo_04.dir/build: ../bin/demo_04

.PHONY : CMakeFiles/demo_04.dir/build

CMakeFiles/demo_04.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/demo_04.dir/cmake_clean.cmake
.PHONY : CMakeFiles/demo_04.dir/clean

CMakeFiles/demo_04.dir/depend:
	cd /home/zjh/Thread/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zjh/Thread /home/zjh/Thread /home/zjh/Thread/build /home/zjh/Thread/build /home/zjh/Thread/build/CMakeFiles/demo_04.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/demo_04.dir/depend

