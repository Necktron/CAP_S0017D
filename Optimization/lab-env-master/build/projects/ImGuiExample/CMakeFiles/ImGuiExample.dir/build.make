# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/build

# Include any dependencies generated for this target.
include projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/depend.make

# Include the progress variables for this target.
include projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/progress.make

# Include the compile flags for this target's objects.
include projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/flags.make

projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.o: projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/flags.make
projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.o: ../projects/ImGuiExample/code/exampleapp.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.o"
	cd /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/build/projects/ImGuiExample && /usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.o -c /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/projects/ImGuiExample/code/exampleapp.cc

projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.i"
	cd /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/build/projects/ImGuiExample && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/projects/ImGuiExample/code/exampleapp.cc > CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.i

projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.s"
	cd /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/build/projects/ImGuiExample && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/projects/ImGuiExample/code/exampleapp.cc -o CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.s

projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.o.requires:

.PHONY : projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.o.requires

projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.o.provides: projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.o.requires
	$(MAKE) -f projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/build.make projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.o.provides.build
.PHONY : projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.o.provides

projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.o.provides.build: projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.o


projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/main.cc.o: projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/flags.make
projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/main.cc.o: ../projects/ImGuiExample/code/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/main.cc.o"
	cd /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/build/projects/ImGuiExample && /usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ImGuiExample.dir/code/main.cc.o -c /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/projects/ImGuiExample/code/main.cc

projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ImGuiExample.dir/code/main.cc.i"
	cd /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/build/projects/ImGuiExample && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/projects/ImGuiExample/code/main.cc > CMakeFiles/ImGuiExample.dir/code/main.cc.i

projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ImGuiExample.dir/code/main.cc.s"
	cd /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/build/projects/ImGuiExample && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/projects/ImGuiExample/code/main.cc -o CMakeFiles/ImGuiExample.dir/code/main.cc.s

projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/main.cc.o.requires:

.PHONY : projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/main.cc.o.requires

projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/main.cc.o.provides: projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/main.cc.o.requires
	$(MAKE) -f projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/build.make projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/main.cc.o.provides.build
.PHONY : projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/main.cc.o.provides

projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/main.cc.o.provides.build: projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/main.cc.o


# Object files for target ImGuiExample
ImGuiExample_OBJECTS = \
"CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.o" \
"CMakeFiles/ImGuiExample.dir/code/main.cc.o"

# External object files for target ImGuiExample
ImGuiExample_EXTERNAL_OBJECTS =

../bin/ImGuiExample: projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.o
../bin/ImGuiExample: projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/main.cc.o
../bin/ImGuiExample: projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/build.make
../bin/ImGuiExample: engine/core/libcore.a
../bin/ImGuiExample: engine/render/librender.a
../bin/ImGuiExample: exts/glew/libglew.a
../bin/ImGuiExample: exts/glfw-3.1.1/src/libglfw3.a
../bin/ImGuiExample: exts/libimgui.a
../bin/ImGuiExample: exts/libnanovg.a
../bin/ImGuiExample: exts/libimgui.a
../bin/ImGuiExample: exts/libnanovg.a
../bin/ImGuiExample: projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../../bin/ImGuiExample"
	cd /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/build/projects/ImGuiExample && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ImGuiExample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/build: ../bin/ImGuiExample

.PHONY : projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/build

projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/requires: projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/exampleapp.cc.o.requires
projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/requires: projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/code/main.cc.o.requires

.PHONY : projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/requires

projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/clean:
	cd /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/build/projects/ImGuiExample && $(CMAKE_COMMAND) -P CMakeFiles/ImGuiExample.dir/cmake_clean.cmake
.PHONY : projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/clean

projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/depend:
	cd /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/projects/ImGuiExample /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/build /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/build/projects/ImGuiExample /home/nacken/Documents/University/LTU/CAP_S0017D/Optimization/lab-env-master/build/projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : projects/ImGuiExample/CMakeFiles/ImGuiExample.dir/depend

