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
include CMakeFiles/fuse_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fuse_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fuse_test.dir/flags.make

CMakeFiles/fuse_test.dir/code/src/fuse_test.c.o: CMakeFiles/fuse_test.dir/flags.make
CMakeFiles/fuse_test.dir/code/src/fuse_test.c.o: ../code/src/fuse_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zjh/wz_riscv/github/Test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/fuse_test.dir/code/src/fuse_test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/fuse_test.dir/code/src/fuse_test.c.o   -c /home/zjh/wz_riscv/github/Test/code/src/fuse_test.c

CMakeFiles/fuse_test.dir/code/src/fuse_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fuse_test.dir/code/src/fuse_test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/zjh/wz_riscv/github/Test/code/src/fuse_test.c > CMakeFiles/fuse_test.dir/code/src/fuse_test.c.i

CMakeFiles/fuse_test.dir/code/src/fuse_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fuse_test.dir/code/src/fuse_test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/zjh/wz_riscv/github/Test/code/src/fuse_test.c -o CMakeFiles/fuse_test.dir/code/src/fuse_test.c.s

CMakeFiles/fuse_test.dir/code/src/fuse_fun.c.o: CMakeFiles/fuse_test.dir/flags.make
CMakeFiles/fuse_test.dir/code/src/fuse_fun.c.o: ../code/src/fuse_fun.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zjh/wz_riscv/github/Test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/fuse_test.dir/code/src/fuse_fun.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/fuse_test.dir/code/src/fuse_fun.c.o   -c /home/zjh/wz_riscv/github/Test/code/src/fuse_fun.c

CMakeFiles/fuse_test.dir/code/src/fuse_fun.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fuse_test.dir/code/src/fuse_fun.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/zjh/wz_riscv/github/Test/code/src/fuse_fun.c > CMakeFiles/fuse_test.dir/code/src/fuse_fun.c.i

CMakeFiles/fuse_test.dir/code/src/fuse_fun.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fuse_test.dir/code/src/fuse_fun.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/zjh/wz_riscv/github/Test/code/src/fuse_fun.c -o CMakeFiles/fuse_test.dir/code/src/fuse_fun.c.s

# Object files for target fuse_test
fuse_test_OBJECTS = \
"CMakeFiles/fuse_test.dir/code/src/fuse_test.c.o" \
"CMakeFiles/fuse_test.dir/code/src/fuse_fun.c.o"

# External object files for target fuse_test
fuse_test_EXTERNAL_OBJECTS =

../bin/fuse_test: CMakeFiles/fuse_test.dir/code/src/fuse_test.c.o
../bin/fuse_test: CMakeFiles/fuse_test.dir/code/src/fuse_fun.c.o
../bin/fuse_test: CMakeFiles/fuse_test.dir/build.make
../bin/fuse_test: ../lib/libmain_library.a
../bin/fuse_test: CMakeFiles/fuse_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zjh/wz_riscv/github/Test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../bin/fuse_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fuse_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fuse_test.dir/build: ../bin/fuse_test

.PHONY : CMakeFiles/fuse_test.dir/build

CMakeFiles/fuse_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fuse_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fuse_test.dir/clean

CMakeFiles/fuse_test.dir/depend:
	cd /home/zjh/wz_riscv/github/Test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zjh/wz_riscv/github/Test /home/zjh/wz_riscv/github/Test /home/zjh/wz_riscv/github/Test/build /home/zjh/wz_riscv/github/Test/build /home/zjh/wz_riscv/github/Test/build/CMakeFiles/fuse_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fuse_test.dir/depend

