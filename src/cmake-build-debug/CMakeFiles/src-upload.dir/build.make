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

# Utility rule file for src-upload.

# Include the progress variables for this target.
include CMakeFiles/src-upload.dir/progress.make

CMakeFiles/src-upload: src.elf
	/home/shchuko/.user_apps/arduino-1.8.9/hardware/tools/avr/bin/avrdude -C/home/shchuko/.user_apps/arduino-1.8.9/hardware/tools/avr/etc/avrdude.conf -patmega328p -carduino -b57600 -P/dev/ttyUSB0 -D -V -Uflash:w:/home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/src.hex:i -Ueeprom:w:/home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/src.eep:i

src-upload: CMakeFiles/src-upload
src-upload: CMakeFiles/src-upload.dir/build.make

.PHONY : src-upload

# Rule to build all files generated by this target.
CMakeFiles/src-upload.dir/build: src-upload

.PHONY : CMakeFiles/src-upload.dir/build

CMakeFiles/src-upload.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/src-upload.dir/cmake_clean.cmake
.PHONY : CMakeFiles/src-upload.dir/clean

CMakeFiles/src-upload.dir/depend:
	cd /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shchuko/P/Arduino/BusyBoard/src /home/shchuko/P/Arduino/BusyBoard/src /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug /home/shchuko/P/Arduino/BusyBoard/src/cmake-build-debug/CMakeFiles/src-upload.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/src-upload.dir/depend

