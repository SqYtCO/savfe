# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/me/software/applications/savfe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/me/software/applications/savfe

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/me/software/applications/savfe/CMakeFiles /home/me/software/applications/savfe/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/me/software/applications/savfe/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named headers

# Build rule for target.
headers: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 headers
.PHONY : headers

# fast build rule for target.
headers/fast:
	$(MAKE) -f CMakeFiles/headers.dir/build.make CMakeFiles/headers.dir/build
.PHONY : headers/fast

#=============================================================================
# Target rules for targets named savfe

# Build rule for target.
savfe: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 savfe
.PHONY : savfe

# fast build rule for target.
savfe/fast:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/build
.PHONY : savfe/fast

dir_functions.o: dir_functions.cpp.o

.PHONY : dir_functions.o

# target to build an object file
dir_functions.cpp.o:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/dir_functions.cpp.o
.PHONY : dir_functions.cpp.o

dir_functions.i: dir_functions.cpp.i

.PHONY : dir_functions.i

# target to preprocess a source file
dir_functions.cpp.i:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/dir_functions.cpp.i
.PHONY : dir_functions.cpp.i

dir_functions.s: dir_functions.cpp.s

.PHONY : dir_functions.s

# target to generate assembly for a file
dir_functions.cpp.s:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/dir_functions.cpp.s
.PHONY : dir_functions.cpp.s

input.o: input.cpp.o

.PHONY : input.o

# target to build an object file
input.cpp.o:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/input.cpp.o
.PHONY : input.cpp.o

input.i: input.cpp.i

.PHONY : input.i

# target to preprocess a source file
input.cpp.i:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/input.cpp.i
.PHONY : input.cpp.i

input.s: input.cpp.s

.PHONY : input.s

# target to generate assembly for a file
input.cpp.s:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/input.cpp.s
.PHONY : input.cpp.s

log.o: log.cpp.o

.PHONY : log.o

# target to build an object file
log.cpp.o:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/log.cpp.o
.PHONY : log.cpp.o

log.i: log.cpp.i

.PHONY : log.i

# target to preprocess a source file
log.cpp.i:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/log.cpp.i
.PHONY : log.cpp.i

log.s: log.cpp.s

.PHONY : log.s

# target to generate assembly for a file
log.cpp.s:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/log.cpp.s
.PHONY : log.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/main.cpp.s
.PHONY : main.cpp.s

parameters.o: parameters.cpp.o

.PHONY : parameters.o

# target to build an object file
parameters.cpp.o:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/parameters.cpp.o
.PHONY : parameters.cpp.o

parameters.i: parameters.cpp.i

.PHONY : parameters.i

# target to preprocess a source file
parameters.cpp.i:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/parameters.cpp.i
.PHONY : parameters.cpp.i

parameters.s: parameters.cpp.s

.PHONY : parameters.s

# target to generate assembly for a file
parameters.cpp.s:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/parameters.cpp.s
.PHONY : parameters.cpp.s

run.o: run.cpp.o

.PHONY : run.o

# target to build an object file
run.cpp.o:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/run.cpp.o
.PHONY : run.cpp.o

run.i: run.cpp.i

.PHONY : run.i

# target to preprocess a source file
run.cpp.i:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/run.cpp.i
.PHONY : run.cpp.i

run.s: run.cpp.s

.PHONY : run.s

# target to generate assembly for a file
run.cpp.s:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/run.cpp.s
.PHONY : run.cpp.s

settings.o: settings.cpp.o

.PHONY : settings.o

# target to build an object file
settings.cpp.o:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/settings.cpp.o
.PHONY : settings.cpp.o

settings.i: settings.cpp.i

.PHONY : settings.i

# target to preprocess a source file
settings.cpp.i:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/settings.cpp.i
.PHONY : settings.cpp.i

settings.s: settings.cpp.s

.PHONY : settings.s

# target to generate assembly for a file
settings.cpp.s:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/settings.cpp.s
.PHONY : settings.cpp.s

terminal.o: terminal.cpp.o

.PHONY : terminal.o

# target to build an object file
terminal.cpp.o:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/terminal.cpp.o
.PHONY : terminal.cpp.o

terminal.i: terminal.cpp.i

.PHONY : terminal.i

# target to preprocess a source file
terminal.cpp.i:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/terminal.cpp.i
.PHONY : terminal.cpp.i

terminal.s: terminal.cpp.s

.PHONY : terminal.s

# target to generate assembly for a file
terminal.cpp.s:
	$(MAKE) -f CMakeFiles/savfe.dir/build.make CMakeFiles/savfe.dir/terminal.cpp.s
.PHONY : terminal.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... headers"
	@echo "... savfe"
	@echo "... dir_functions.o"
	@echo "... dir_functions.i"
	@echo "... dir_functions.s"
	@echo "... input.o"
	@echo "... input.i"
	@echo "... input.s"
	@echo "... log.o"
	@echo "... log.i"
	@echo "... log.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... parameters.o"
	@echo "... parameters.i"
	@echo "... parameters.s"
	@echo "... run.o"
	@echo "... run.i"
	@echo "... run.s"
	@echo "... settings.o"
	@echo "... settings.i"
	@echo "... settings.s"
	@echo "... terminal.o"
	@echo "... terminal.i"
	@echo "... terminal.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

