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
include CMakeFiles/BusyBoard.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BusyBoard.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BusyBoard.dir/flags.make

BusyBoard_busy_board.ino.cpp: ../busy_board.ino
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Regnerating busy_board.ino Sketch"
	/home/shchuko/.user_apps/clion-2018.3.4/bin/cmake/linux/bin/cmake /home/shchuko/P/Arduino/BusyBoard/src

CMakeFiles/BusyBoard.dir/BusyBoard_busy_board.ino.cpp.obj: CMakeFiles/BusyBoard.dir/flags.make
CMakeFiles/BusyBoard.dir/BusyBoard_busy_board.ino.cpp.obj: BusyBoard_busy_board.ino.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BusyBoard.dir/BusyBoard_busy_board.ino.cpp.obj"
	/home/shchuko/.user_apps/arduino-1.8.9/hardware/tools/avr/bin/avr-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BusyBoard.dir/BusyBoard_busy_board.ino.cpp.obj -c /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/BusyBoard_busy_board.ino.cpp

CMakeFiles/BusyBoard.dir/BusyBoard_busy_board.ino.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BusyBoard.dir/BusyBoard_busy_board.ino.cpp.i"
	/home/shchuko/.user_apps/arduino-1.8.9/hardware/tools/avr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/BusyBoard_busy_board.ino.cpp > CMakeFiles/BusyBoard.dir/BusyBoard_busy_board.ino.cpp.i

CMakeFiles/BusyBoard.dir/BusyBoard_busy_board.ino.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BusyBoard.dir/BusyBoard_busy_board.ino.cpp.s"
	/home/shchuko/.user_apps/arduino-1.8.9/hardware/tools/avr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/BusyBoard_busy_board.ino.cpp -o CMakeFiles/BusyBoard.dir/BusyBoard_busy_board.ino.cpp.s

# Object files for target BusyBoard
BusyBoard_OBJECTS = \
"CMakeFiles/BusyBoard.dir/BusyBoard_busy_board.ino.cpp.obj"

# External object files for target BusyBoard
BusyBoard_EXTERNAL_OBJECTS =

BusyBoard.elf: CMakeFiles/BusyBoard.dir/BusyBoard_busy_board.ino.cpp.obj
BusyBoard.elf: CMakeFiles/BusyBoard.dir/build.make
BusyBoard.elf: libmini_DFMiniMp3.a
BusyBoard.elf: libmini_Keypad.a
BusyBoard.elf: libmini_Key.a
BusyBoard.elf: libmini_CORE.a
BusyBoard.elf: CMakeFiles/BusyBoard.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable BusyBoard.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BusyBoard.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating EEP image"
	/home/shchuko/.user_apps/arduino-1.8.9/hardware/tools/avr/bin/avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/BusyBoard.elf /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/BusyBoard.eep
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating HEX image"
	/home/shchuko/.user_apps/arduino-1.8.9/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/BusyBoard.elf /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/BusyBoard.hex
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Calculating image size"
	/home/shchuko/.user_apps/clion-2018.3.4/bin/cmake/linux/bin/cmake -DFIRMWARE_IMAGE=/home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/BusyBoard.elf -DMCU=atmega328p -DEEPROM_IMAGE=/home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/BusyBoard.eep -P /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/CMakeFiles/FirmwareSize.cmake

# Rule to build all files generated by this target.
CMakeFiles/BusyBoard.dir/build: BusyBoard.elf

.PHONY : CMakeFiles/BusyBoard.dir/build

CMakeFiles/BusyBoard.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BusyBoard.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BusyBoard.dir/clean

CMakeFiles/BusyBoard.dir/depend: BusyBoard_busy_board.ino.cpp
	cd /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shchuko/P/Arduino/BusyBoard/src /home/shchuko/P/Arduino/BusyBoard/src /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/CMakeFiles/BusyBoard.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BusyBoard.dir/depend

