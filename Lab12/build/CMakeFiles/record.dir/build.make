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
CMAKE_SOURCE_DIR = /home/tomasz/Documents/Studia/SCR_Systemy_Operacyjne/Lab12

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tomasz/Documents/Studia/SCR_Systemy_Operacyjne/Lab12/build

# Include any dependencies generated for this target.
include CMakeFiles/record.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/record.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/record.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/record.dir/flags.make

CMakeFiles/record.dir/src/record.cpp.o: CMakeFiles/record.dir/flags.make
CMakeFiles/record.dir/src/record.cpp.o: ../src/record.cpp
CMakeFiles/record.dir/src/record.cpp.o: CMakeFiles/record.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tomasz/Documents/Studia/SCR_Systemy_Operacyjne/Lab12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/record.dir/src/record.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/record.dir/src/record.cpp.o -MF CMakeFiles/record.dir/src/record.cpp.o.d -o CMakeFiles/record.dir/src/record.cpp.o -c /home/tomasz/Documents/Studia/SCR_Systemy_Operacyjne/Lab12/src/record.cpp

CMakeFiles/record.dir/src/record.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/record.dir/src/record.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tomasz/Documents/Studia/SCR_Systemy_Operacyjne/Lab12/src/record.cpp > CMakeFiles/record.dir/src/record.cpp.i

CMakeFiles/record.dir/src/record.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/record.dir/src/record.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tomasz/Documents/Studia/SCR_Systemy_Operacyjne/Lab12/src/record.cpp -o CMakeFiles/record.dir/src/record.cpp.s

# Object files for target record
record_OBJECTS = \
"CMakeFiles/record.dir/src/record.cpp.o"

# External object files for target record
record_EXTERNAL_OBJECTS =

librecord.a: CMakeFiles/record.dir/src/record.cpp.o
librecord.a: CMakeFiles/record.dir/build.make
librecord.a: CMakeFiles/record.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tomasz/Documents/Studia/SCR_Systemy_Operacyjne/Lab12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library librecord.a"
	$(CMAKE_COMMAND) -P CMakeFiles/record.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/record.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/record.dir/build: librecord.a
.PHONY : CMakeFiles/record.dir/build

CMakeFiles/record.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/record.dir/cmake_clean.cmake
.PHONY : CMakeFiles/record.dir/clean

CMakeFiles/record.dir/depend:
	cd /home/tomasz/Documents/Studia/SCR_Systemy_Operacyjne/Lab12/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tomasz/Documents/Studia/SCR_Systemy_Operacyjne/Lab12 /home/tomasz/Documents/Studia/SCR_Systemy_Operacyjne/Lab12 /home/tomasz/Documents/Studia/SCR_Systemy_Operacyjne/Lab12/build /home/tomasz/Documents/Studia/SCR_Systemy_Operacyjne/Lab12/build /home/tomasz/Documents/Studia/SCR_Systemy_Operacyjne/Lab12/build/CMakeFiles/record.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/record.dir/depend
