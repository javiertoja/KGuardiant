# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/karels/Dropbox/Fic/CAIT/TFG/KGuardiant/KGuardiant/KGuardiant_console

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/karels/Dropbox/Fic/CAIT/TFG/KGuardiant/KGuardiant/KGuardiant_console-build

# Include any dependencies generated for this target.
include CMakeFiles/KGuardiant_console.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/KGuardiant_console.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/KGuardiant_console.dir/flags.make

CMakeFiles/KGuardiant_console.dir/main.cpp.o: CMakeFiles/KGuardiant_console.dir/flags.make
CMakeFiles/KGuardiant_console.dir/main.cpp.o: /home/karels/Dropbox/Fic/CAIT/TFG/KGuardiant/KGuardiant/KGuardiant_console/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/karels/Dropbox/Fic/CAIT/TFG/KGuardiant/KGuardiant/KGuardiant_console-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/KGuardiant_console.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/KGuardiant_console.dir/main.cpp.o -c /home/karels/Dropbox/Fic/CAIT/TFG/KGuardiant/KGuardiant/KGuardiant_console/main.cpp

CMakeFiles/KGuardiant_console.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KGuardiant_console.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/karels/Dropbox/Fic/CAIT/TFG/KGuardiant/KGuardiant/KGuardiant_console/main.cpp > CMakeFiles/KGuardiant_console.dir/main.cpp.i

CMakeFiles/KGuardiant_console.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KGuardiant_console.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/karels/Dropbox/Fic/CAIT/TFG/KGuardiant/KGuardiant/KGuardiant_console/main.cpp -o CMakeFiles/KGuardiant_console.dir/main.cpp.s

CMakeFiles/KGuardiant_console.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/KGuardiant_console.dir/main.cpp.o.requires

CMakeFiles/KGuardiant_console.dir/main.cpp.o.provides: CMakeFiles/KGuardiant_console.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/KGuardiant_console.dir/build.make CMakeFiles/KGuardiant_console.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/KGuardiant_console.dir/main.cpp.o.provides

CMakeFiles/KGuardiant_console.dir/main.cpp.o.provides.build: CMakeFiles/KGuardiant_console.dir/main.cpp.o

# Object files for target KGuardiant_console
KGuardiant_console_OBJECTS = \
"CMakeFiles/KGuardiant_console.dir/main.cpp.o"

# External object files for target KGuardiant_console
KGuardiant_console_EXTERNAL_OBJECTS =

KGuardiant_console: CMakeFiles/KGuardiant_console.dir/main.cpp.o
KGuardiant_console: CMakeFiles/KGuardiant_console.dir/build.make
KGuardiant_console: CMakeFiles/KGuardiant_console.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable KGuardiant_console"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/KGuardiant_console.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/KGuardiant_console.dir/build: KGuardiant_console
.PHONY : CMakeFiles/KGuardiant_console.dir/build

CMakeFiles/KGuardiant_console.dir/requires: CMakeFiles/KGuardiant_console.dir/main.cpp.o.requires
.PHONY : CMakeFiles/KGuardiant_console.dir/requires

CMakeFiles/KGuardiant_console.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/KGuardiant_console.dir/cmake_clean.cmake
.PHONY : CMakeFiles/KGuardiant_console.dir/clean

CMakeFiles/KGuardiant_console.dir/depend:
	cd /home/karels/Dropbox/Fic/CAIT/TFG/KGuardiant/KGuardiant/KGuardiant_console-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/karels/Dropbox/Fic/CAIT/TFG/KGuardiant/KGuardiant/KGuardiant_console /home/karels/Dropbox/Fic/CAIT/TFG/KGuardiant/KGuardiant/KGuardiant_console /home/karels/Dropbox/Fic/CAIT/TFG/KGuardiant/KGuardiant/KGuardiant_console-build /home/karels/Dropbox/Fic/CAIT/TFG/KGuardiant/KGuardiant/KGuardiant_console-build /home/karels/Dropbox/Fic/CAIT/TFG/KGuardiant/KGuardiant/KGuardiant_console-build/CMakeFiles/KGuardiant_console.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/KGuardiant_console.dir/depend

