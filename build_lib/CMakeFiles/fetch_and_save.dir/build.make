# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/alex/Documents/code/basealt_test/shared_lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/Documents/code/basealt_test/build

# Include any dependencies generated for this target.
include CMakeFiles/fetch_and_save.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/fetch_and_save.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/fetch_and_save.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fetch_and_save.dir/flags.make

CMakeFiles/fetch_and_save.dir/fetch_and_save.cpp.o: CMakeFiles/fetch_and_save.dir/flags.make
CMakeFiles/fetch_and_save.dir/fetch_and_save.cpp.o: /home/alex/Documents/code/basealt_test/shared_lib/fetch_and_save.cpp
CMakeFiles/fetch_and_save.dir/fetch_and_save.cpp.o: CMakeFiles/fetch_and_save.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/alex/Documents/code/basealt_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fetch_and_save.dir/fetch_and_save.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/fetch_and_save.dir/fetch_and_save.cpp.o -MF CMakeFiles/fetch_and_save.dir/fetch_and_save.cpp.o.d -o CMakeFiles/fetch_and_save.dir/fetch_and_save.cpp.o -c /home/alex/Documents/code/basealt_test/shared_lib/fetch_and_save.cpp

CMakeFiles/fetch_and_save.dir/fetch_and_save.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fetch_and_save.dir/fetch_and_save.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Documents/code/basealt_test/shared_lib/fetch_and_save.cpp > CMakeFiles/fetch_and_save.dir/fetch_and_save.cpp.i

CMakeFiles/fetch_and_save.dir/fetch_and_save.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fetch_and_save.dir/fetch_and_save.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Documents/code/basealt_test/shared_lib/fetch_and_save.cpp -o CMakeFiles/fetch_and_save.dir/fetch_and_save.cpp.s

# Object files for target fetch_and_save
fetch_and_save_OBJECTS = \
"CMakeFiles/fetch_and_save.dir/fetch_and_save.cpp.o"

# External object files for target fetch_and_save
fetch_and_save_EXTERNAL_OBJECTS =

libfetch_and_save.so: CMakeFiles/fetch_and_save.dir/fetch_and_save.cpp.o
libfetch_and_save.so: CMakeFiles/fetch_and_save.dir/build.make
libfetch_and_save.so: CMakeFiles/fetch_and_save.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/alex/Documents/code/basealt_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libfetch_and_save.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fetch_and_save.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fetch_and_save.dir/build: libfetch_and_save.so
.PHONY : CMakeFiles/fetch_and_save.dir/build

CMakeFiles/fetch_and_save.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fetch_and_save.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fetch_and_save.dir/clean

CMakeFiles/fetch_and_save.dir/depend:
	cd /home/alex/Documents/code/basealt_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/Documents/code/basealt_test/shared_lib /home/alex/Documents/code/basealt_test/shared_lib /home/alex/Documents/code/basealt_test/build /home/alex/Documents/code/basealt_test/build /home/alex/Documents/code/basealt_test/build/CMakeFiles/fetch_and_save.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/fetch_and_save.dir/depend

