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
include CMakeFiles/file_S.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/file_S.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/file_S.dir/flags.make

CMakeFiles/file_S.dir/src/file_S.cpp.o: CMakeFiles/file_S.dir/flags.make
CMakeFiles/file_S.dir/src/file_S.cpp.o: ../src/file_S.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zjh/Linux_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/file_S.dir/src/file_S.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/file_S.dir/src/file_S.cpp.o -c /home/zjh/Linux_demo/src/file_S.cpp

CMakeFiles/file_S.dir/src/file_S.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/file_S.dir/src/file_S.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zjh/Linux_demo/src/file_S.cpp > CMakeFiles/file_S.dir/src/file_S.cpp.i

CMakeFiles/file_S.dir/src/file_S.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/file_S.dir/src/file_S.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zjh/Linux_demo/src/file_S.cpp -o CMakeFiles/file_S.dir/src/file_S.cpp.s

# Object files for target file_S
file_S_OBJECTS = \
"CMakeFiles/file_S.dir/src/file_S.cpp.o"

# External object files for target file_S
file_S_EXTERNAL_OBJECTS =

../bin/file_S: CMakeFiles/file_S.dir/src/file_S.cpp.o
../bin/file_S: CMakeFiles/file_S.dir/build.make
../bin/file_S: /usr/lib/x86_64-linux-gnu/libz.so
../bin/file_S: /usr/lib/x86_64-linux-gnu/libzip.so
../bin/file_S: CMakeFiles/file_S.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zjh/Linux_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/file_S"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/file_S.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/file_S.dir/build: ../bin/file_S

.PHONY : CMakeFiles/file_S.dir/build

CMakeFiles/file_S.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/file_S.dir/cmake_clean.cmake
.PHONY : CMakeFiles/file_S.dir/clean

CMakeFiles/file_S.dir/depend:
	cd /home/zjh/Linux_demo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zjh/Linux_demo /home/zjh/Linux_demo /home/zjh/Linux_demo/build /home/zjh/Linux_demo/build /home/zjh/Linux_demo/build/CMakeFiles/file_S.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/file_S.dir/depend

