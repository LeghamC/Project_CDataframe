# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.3.4\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.3.4\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\lelia\CLion projects\Project_CDataframe"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\lelia\CLion projects\Project_CDataframe\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/CDataFrame.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CDataFrame.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CDataFrame.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CDataFrame.dir/flags.make

CMakeFiles/CDataFrame.dir/main.c.obj: CMakeFiles/CDataFrame.dir/flags.make
CMakeFiles/CDataFrame.dir/main.c.obj: C:/Users/lelia/CLion\ projects/Project_CDataframe/main.c
CMakeFiles/CDataFrame.dir/main.c.obj: CMakeFiles/CDataFrame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\lelia\CLion projects\Project_CDataframe\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CDataFrame.dir/main.c.obj"
	C:\PROGRA~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CDataFrame.dir/main.c.obj -MF CMakeFiles\CDataFrame.dir\main.c.obj.d -o CMakeFiles\CDataFrame.dir\main.c.obj -c "C:\Users\lelia\CLion projects\Project_CDataframe\main.c"

CMakeFiles/CDataFrame.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CDataFrame.dir/main.c.i"
	C:\PROGRA~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\lelia\CLion projects\Project_CDataframe\main.c" > CMakeFiles\CDataFrame.dir\main.c.i

CMakeFiles/CDataFrame.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CDataFrame.dir/main.c.s"
	C:\PROGRA~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\lelia\CLion projects\Project_CDataframe\main.c" -o CMakeFiles\CDataFrame.dir\main.c.s

CMakeFiles/CDataFrame.dir/column.c.obj: CMakeFiles/CDataFrame.dir/flags.make
CMakeFiles/CDataFrame.dir/column.c.obj: C:/Users/lelia/CLion\ projects/Project_CDataframe/column.c
CMakeFiles/CDataFrame.dir/column.c.obj: CMakeFiles/CDataFrame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\lelia\CLion projects\Project_CDataframe\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/CDataFrame.dir/column.c.obj"
	C:\PROGRA~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CDataFrame.dir/column.c.obj -MF CMakeFiles\CDataFrame.dir\column.c.obj.d -o CMakeFiles\CDataFrame.dir\column.c.obj -c "C:\Users\lelia\CLion projects\Project_CDataframe\column.c"

CMakeFiles/CDataFrame.dir/column.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CDataFrame.dir/column.c.i"
	C:\PROGRA~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\lelia\CLion projects\Project_CDataframe\column.c" > CMakeFiles\CDataFrame.dir\column.c.i

CMakeFiles/CDataFrame.dir/column.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CDataFrame.dir/column.c.s"
	C:\PROGRA~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\lelia\CLion projects\Project_CDataframe\column.c" -o CMakeFiles\CDataFrame.dir\column.c.s

# Object files for target CDataFrame
CDataFrame_OBJECTS = \
"CMakeFiles/CDataFrame.dir/main.c.obj" \
"CMakeFiles/CDataFrame.dir/column.c.obj"

# External object files for target CDataFrame
CDataFrame_EXTERNAL_OBJECTS =

CDataFrame.exe: CMakeFiles/CDataFrame.dir/main.c.obj
CDataFrame.exe: CMakeFiles/CDataFrame.dir/column.c.obj
CDataFrame.exe: CMakeFiles/CDataFrame.dir/build.make
CDataFrame.exe: CMakeFiles/CDataFrame.dir/linkLibs.rsp
CDataFrame.exe: CMakeFiles/CDataFrame.dir/objects1.rsp
CDataFrame.exe: CMakeFiles/CDataFrame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:\Users\lelia\CLion projects\Project_CDataframe\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable CDataFrame.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\CDataFrame.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CDataFrame.dir/build: CDataFrame.exe
.PHONY : CMakeFiles/CDataFrame.dir/build

CMakeFiles/CDataFrame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\CDataFrame.dir\cmake_clean.cmake
.PHONY : CMakeFiles/CDataFrame.dir/clean

CMakeFiles/CDataFrame.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\lelia\CLion projects\Project_CDataframe" "C:\Users\lelia\CLion projects\Project_CDataframe" "C:\Users\lelia\CLion projects\Project_CDataframe\cmake-build-debug" "C:\Users\lelia\CLion projects\Project_CDataframe\cmake-build-debug" "C:\Users\lelia\CLion projects\Project_CDataframe\cmake-build-debug\CMakeFiles\CDataFrame.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/CDataFrame.dir/depend

