# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\Alexey\My\Apps\Special\DevTools\Cmake\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Alexey\My\Apps\Special\DevTools\Cmake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\build

# Include any dependencies generated for this target.
include CMakeFiles/benchmark.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/benchmark.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/benchmark.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/benchmark.dir/flags.make

CMakeFiles/benchmark.dir/src/benchmark.cpp.obj: CMakeFiles/benchmark.dir/flags.make
CMakeFiles/benchmark.dir/src/benchmark.cpp.obj: CMakeFiles/benchmark.dir/includes_CXX.rsp
CMakeFiles/benchmark.dir/src/benchmark.cpp.obj: C:/Users/Alexey/My/Files/Projects/StudyProjects/networking/benchmark/benchmark/src/benchmark.cpp
CMakeFiles/benchmark.dir/src/benchmark.cpp.obj: CMakeFiles/benchmark.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/benchmark.dir/src/benchmark.cpp.obj"
	C:\Users\Alexey\My\Apps\Special\DevTools\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/benchmark.dir/src/benchmark.cpp.obj -MF CMakeFiles\benchmark.dir\src\benchmark.cpp.obj.d -o CMakeFiles\benchmark.dir\src\benchmark.cpp.obj -c C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\src\benchmark.cpp

CMakeFiles/benchmark.dir/src/benchmark.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/src/benchmark.cpp.i"
	C:\Users\Alexey\My\Apps\Special\DevTools\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\src\benchmark.cpp > CMakeFiles\benchmark.dir\src\benchmark.cpp.i

CMakeFiles/benchmark.dir/src/benchmark.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/src/benchmark.cpp.s"
	C:\Users\Alexey\My\Apps\Special\DevTools\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\src\benchmark.cpp -o CMakeFiles\benchmark.dir\src\benchmark.cpp.s

CMakeFiles/benchmark.dir/src/sockets.cpp.obj: CMakeFiles/benchmark.dir/flags.make
CMakeFiles/benchmark.dir/src/sockets.cpp.obj: CMakeFiles/benchmark.dir/includes_CXX.rsp
CMakeFiles/benchmark.dir/src/sockets.cpp.obj: C:/Users/Alexey/My/Files/Projects/StudyProjects/networking/benchmark/benchmark/src/sockets.cpp
CMakeFiles/benchmark.dir/src/sockets.cpp.obj: CMakeFiles/benchmark.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/benchmark.dir/src/sockets.cpp.obj"
	C:\Users\Alexey\My\Apps\Special\DevTools\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/benchmark.dir/src/sockets.cpp.obj -MF CMakeFiles\benchmark.dir\src\sockets.cpp.obj.d -o CMakeFiles\benchmark.dir\src\sockets.cpp.obj -c C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\src\sockets.cpp

CMakeFiles/benchmark.dir/src/sockets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/src/sockets.cpp.i"
	C:\Users\Alexey\My\Apps\Special\DevTools\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\src\sockets.cpp > CMakeFiles\benchmark.dir\src\sockets.cpp.i

CMakeFiles/benchmark.dir/src/sockets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/src/sockets.cpp.s"
	C:\Users\Alexey\My\Apps\Special\DevTools\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\src\sockets.cpp -o CMakeFiles\benchmark.dir\src\sockets.cpp.s

CMakeFiles/benchmark.dir/src/tests.cpp.obj: CMakeFiles/benchmark.dir/flags.make
CMakeFiles/benchmark.dir/src/tests.cpp.obj: CMakeFiles/benchmark.dir/includes_CXX.rsp
CMakeFiles/benchmark.dir/src/tests.cpp.obj: C:/Users/Alexey/My/Files/Projects/StudyProjects/networking/benchmark/benchmark/src/tests.cpp
CMakeFiles/benchmark.dir/src/tests.cpp.obj: CMakeFiles/benchmark.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/benchmark.dir/src/tests.cpp.obj"
	C:\Users\Alexey\My\Apps\Special\DevTools\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/benchmark.dir/src/tests.cpp.obj -MF CMakeFiles\benchmark.dir\src\tests.cpp.obj.d -o CMakeFiles\benchmark.dir\src\tests.cpp.obj -c C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\src\tests.cpp

CMakeFiles/benchmark.dir/src/tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/src/tests.cpp.i"
	C:\Users\Alexey\My\Apps\Special\DevTools\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\src\tests.cpp > CMakeFiles\benchmark.dir\src\tests.cpp.i

CMakeFiles/benchmark.dir/src/tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/src/tests.cpp.s"
	C:\Users\Alexey\My\Apps\Special\DevTools\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\src\tests.cpp -o CMakeFiles\benchmark.dir\src\tests.cpp.s

CMakeFiles/benchmark.dir/src/stat.cpp.obj: CMakeFiles/benchmark.dir/flags.make
CMakeFiles/benchmark.dir/src/stat.cpp.obj: CMakeFiles/benchmark.dir/includes_CXX.rsp
CMakeFiles/benchmark.dir/src/stat.cpp.obj: C:/Users/Alexey/My/Files/Projects/StudyProjects/networking/benchmark/benchmark/src/stat.cpp
CMakeFiles/benchmark.dir/src/stat.cpp.obj: CMakeFiles/benchmark.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/benchmark.dir/src/stat.cpp.obj"
	C:\Users\Alexey\My\Apps\Special\DevTools\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/benchmark.dir/src/stat.cpp.obj -MF CMakeFiles\benchmark.dir\src\stat.cpp.obj.d -o CMakeFiles\benchmark.dir\src\stat.cpp.obj -c C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\src\stat.cpp

CMakeFiles/benchmark.dir/src/stat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/src/stat.cpp.i"
	C:\Users\Alexey\My\Apps\Special\DevTools\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\src\stat.cpp > CMakeFiles\benchmark.dir\src\stat.cpp.i

CMakeFiles/benchmark.dir/src/stat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/src/stat.cpp.s"
	C:\Users\Alexey\My\Apps\Special\DevTools\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\src\stat.cpp -o CMakeFiles\benchmark.dir\src\stat.cpp.s

CMakeFiles/benchmark.dir/src/plotting.cpp.obj: CMakeFiles/benchmark.dir/flags.make
CMakeFiles/benchmark.dir/src/plotting.cpp.obj: CMakeFiles/benchmark.dir/includes_CXX.rsp
CMakeFiles/benchmark.dir/src/plotting.cpp.obj: C:/Users/Alexey/My/Files/Projects/StudyProjects/networking/benchmark/benchmark/src/plotting.cpp
CMakeFiles/benchmark.dir/src/plotting.cpp.obj: CMakeFiles/benchmark.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/benchmark.dir/src/plotting.cpp.obj"
	C:\Users\Alexey\My\Apps\Special\DevTools\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/benchmark.dir/src/plotting.cpp.obj -MF CMakeFiles\benchmark.dir\src\plotting.cpp.obj.d -o CMakeFiles\benchmark.dir\src\plotting.cpp.obj -c C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\src\plotting.cpp

CMakeFiles/benchmark.dir/src/plotting.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/src/plotting.cpp.i"
	C:\Users\Alexey\My\Apps\Special\DevTools\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\src\plotting.cpp > CMakeFiles\benchmark.dir\src\plotting.cpp.i

CMakeFiles/benchmark.dir/src/plotting.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/src/plotting.cpp.s"
	C:\Users\Alexey\My\Apps\Special\DevTools\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\src\plotting.cpp -o CMakeFiles\benchmark.dir\src\plotting.cpp.s

# Object files for target benchmark
benchmark_OBJECTS = \
"CMakeFiles/benchmark.dir/src/benchmark.cpp.obj" \
"CMakeFiles/benchmark.dir/src/sockets.cpp.obj" \
"CMakeFiles/benchmark.dir/src/tests.cpp.obj" \
"CMakeFiles/benchmark.dir/src/stat.cpp.obj" \
"CMakeFiles/benchmark.dir/src/plotting.cpp.obj"

# External object files for target benchmark
benchmark_EXTERNAL_OBJECTS =

benchmark.exe: CMakeFiles/benchmark.dir/src/benchmark.cpp.obj
benchmark.exe: CMakeFiles/benchmark.dir/src/sockets.cpp.obj
benchmark.exe: CMakeFiles/benchmark.dir/src/tests.cpp.obj
benchmark.exe: CMakeFiles/benchmark.dir/src/stat.cpp.obj
benchmark.exe: CMakeFiles/benchmark.dir/src/plotting.cpp.obj
benchmark.exe: CMakeFiles/benchmark.dir/build.make
benchmark.exe: C:/Users/Alexey/My/Files/Projects/StudyProjects/networking/benchmark/benchmark/common/trase/lib/libtrase.a
benchmark.exe: CMakeFiles/benchmark.dir/linkLibs.rsp
benchmark.exe: CMakeFiles/benchmark.dir/objects1.rsp
benchmark.exe: CMakeFiles/benchmark.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable benchmark.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\benchmark.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/benchmark.dir/build: benchmark.exe
.PHONY : CMakeFiles/benchmark.dir/build

CMakeFiles/benchmark.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\benchmark.dir\cmake_clean.cmake
.PHONY : CMakeFiles/benchmark.dir/clean

CMakeFiles/benchmark.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\build C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\build C:\Users\Alexey\My\Files\Projects\StudyProjects\networking\benchmark\benchmark\build\CMakeFiles\benchmark.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/benchmark.dir/depend

