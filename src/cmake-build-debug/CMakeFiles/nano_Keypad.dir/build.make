# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/shchuko/.user_apps/clion-2018.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/shchuko/.user_apps/clion-2018.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shchuko/P/Arduino/BusyBoard/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/nano_Keypad.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/nano_Keypad.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/nano_Keypad.dir/flags.make

CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Key.cpp.obj: CMakeFiles/nano_Keypad.dir/flags.make
CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Key.cpp.obj: /home/shchuko/Arduino/libraries/Keypad/src/Key.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Key.cpp.obj"
	/home/shchuko/.user_apps/arduino-1.8.9/hardware/tools/avr/bin/avr-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Key.cpp.obj -c /home/shchuko/Arduino/libraries/Keypad/src/Key.cpp

CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Key.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Key.cpp.i"
	/home/shchuko/.user_apps/arduino-1.8.9/hardware/tools/avr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shchuko/Arduino/libraries/Keypad/src/Key.cpp > CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Key.cpp.i

CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Key.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Key.cpp.s"
	/home/shchuko/.user_apps/arduino-1.8.9/hardware/tools/avr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shchuko/Arduino/libraries/Keypad/src/Key.cpp -o CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Key.cpp.s

CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Keypad.cpp.obj: CMakeFiles/nano_Keypad.dir/flags.make
CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Keypad.cpp.obj: /home/shchuko/Arduino/libraries/Keypad/src/Keypad.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Keypad.cpp.obj"
	/home/shchuko/.user_apps/arduino-1.8.9/hardware/tools/avr/bin/avr-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Keypad.cpp.obj -c /home/shchuko/Arduino/libraries/Keypad/src/Keypad.cpp

CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Keypad.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Keypad.cpp.i"
	/home/shchuko/.user_apps/arduino-1.8.9/hardware/tools/avr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shchuko/Arduino/libraries/Keypad/src/Keypad.cpp > CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Keypad.cpp.i

CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Keypad.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Keypad.cpp.s"
	/home/shchuko/.user_apps/arduino-1.8.9/hardware/tools/avr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shchuko/Arduino/libraries/Keypad/src/Keypad.cpp -o CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Keypad.cpp.s

# Object files for target nano_Keypad
nano_Keypad_OBJECTS = \
"CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Key.cpp.obj" \
"CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Keypad.cpp.obj"

# External object files for target nano_Keypad
nano_Keypad_EXTERNAL_OBJECTS =

libnano_Keypad.a: CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Key.cpp.obj
libnano_Keypad.a: CMakeFiles/nano_Keypad.dir/home/shchuko/Arduino/libraries/Keypad/src/Keypad.cpp.obj
libnano_Keypad.a: CMakeFiles/nano_Keypad.dir/build.make
libnano_Keypad.a: CMakeFiles/nano_Keypad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libnano_Keypad.a"
	$(CMAKE_COMMAND) -P CMakeFiles/nano_Keypad.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nano_Keypad.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/nano_Keypad.dir/build: libnano_Keypad.a

.PHONY : CMakeFiles/nano_Keypad.dir/build

CMakeFiles/nano_Keypad.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nano_Keypad.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nano_Keypad.dir/clean

CMakeFiles/nano_Keypad.dir/depend:
	cd /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shchuko/P/Arduino/BusyBoard/src /home/shchuko/P/Arduino/BusyBoard/src /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/CMakeFiles/nano_Keypad.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/nano_Keypad.dir/depend
