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
include CMakeFiles/c.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/c.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/c.dir/flags.make

CMakeFiles/c.dir/Test_code/src/c.c.o: CMakeFiles/c.dir/flags.make
CMakeFiles/c.dir/Test_code/src/c.c.o: ../Test_code/src/c.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zjh/wz_riscv/github/Test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/c.dir/Test_code/src/c.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/c.dir/Test_code/src/c.c.o   -c /home/zjh/wz_riscv/github/Test/Test_code/src/c.c

CMakeFiles/c.dir/Test_code/src/c.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/c.dir/Test_code/src/c.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/zjh/wz_riscv/github/Test/Test_code/src/c.c > CMakeFiles/c.dir/Test_code/src/c.c.i

CMakeFiles/c.dir/Test_code/src/c.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/c.dir/Test_code/src/c.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/zjh/wz_riscv/github/Test/Test_code/src/c.c -o CMakeFiles/c.dir/Test_code/src/c.c.s

# Object files for target c
c_OBJECTS = \
"CMakeFiles/c.dir/Test_code/src/c.c.o"

# External object files for target c
c_EXTERNAL_OBJECTS =

../bin/Test/c: CMakeFiles/c.dir/Test_code/src/c.c.o
../bin/Test/c: CMakeFiles/c.dir/build.make
../bin/Test/c: CMakeFiles/c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zjh/wz_riscv/github/Test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../bin/Test/c"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/c.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/c.dir/build: ../bin/Test/c

.PHONY : CMakeFiles/c.dir/build

CMakeFiles/c.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/c.dir/cmake_clean.cmake
.PHONY : CMakeFiles/c.dir/clean

CMakeFiles/c.dir/depend:
	cd /home/zjh/wz_riscv/github/Test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zjh/wz_riscv/github/Test /home/zjh/wz_riscv/github/Test /home/zjh/wz_riscv/github/Test/build /home/zjh/wz_riscv/github/Test/build /home/zjh/wz_riscv/github/Test/build/CMakeFiles/c.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/c.dir/depend

