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
CMAKE_SOURCE_DIR = /home/zjh/wz_riscv/github/Test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zjh/wz_riscv/github/Test/build

# Include any dependencies generated for this target.
include CMakeFiles/open_txt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/open_txt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/open_txt.dir/flags.make

CMakeFiles/open_txt.dir/Test_code/src/open_txt.cpp.o: CMakeFiles/open_txt.dir/flags.make
CMakeFiles/open_txt.dir/Test_code/src/open_txt.cpp.o: ../Test_code/src/open_txt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zjh/wz_riscv/github/Test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/open_txt.dir/Test_code/src/open_txt.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/open_txt.dir/Test_code/src/open_txt.cpp.o -c /home/zjh/wz_riscv/github/Test/Test_code/src/open_txt.cpp

CMakeFiles/open_txt.dir/Test_code/src/open_txt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/open_txt.dir/Test_code/src/open_txt.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zjh/wz_riscv/github/Test/Test_code/src/open_txt.cpp > CMakeFiles/open_txt.dir/Test_code/src/open_txt.cpp.i

CMakeFiles/open_txt.dir/Test_code/src/open_txt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/open_txt.dir/Test_code/src/open_txt.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zjh/wz_riscv/github/Test/Test_code/src/open_txt.cpp -o CMakeFiles/open_txt.dir/Test_code/src/open_txt.cpp.s

# Object files for target open_txt
open_txt_OBJECTS = \
"CMakeFiles/open_txt.dir/Test_code/src/open_txt.cpp.o"

# External object files for target open_txt
open_txt_EXTERNAL_OBJECTS =

../bin/open_txt: CMakeFiles/open_txt.dir/Test_code/src/open_txt.cpp.o
../bin/open_txt: CMakeFiles/open_txt.dir/build.make
../bin/open_txt: CMakeFiles/open_txt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zjh/wz_riscv/github/Test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/open_txt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/open_txt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/open_txt.dir/build: ../bin/open_txt

.PHONY : CMakeFiles/open_txt.dir/build

CMakeFiles/open_txt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/open_txt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/open_txt.dir/clean

CMakeFiles/open_txt.dir/depend:
	cd /home/zjh/wz_riscv/github/Test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zjh/wz_riscv/github/Test /home/zjh/wz_riscv/github/Test /home/zjh/wz_riscv/github/Test/build /home/zjh/wz_riscv/github/Test/build /home/zjh/wz_riscv/github/Test/build/CMakeFiles/open_txt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/open_txt.dir/depend

