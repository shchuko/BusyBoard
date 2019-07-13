cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 11)
set(PROJECT_NAME src)

set(${PROJECT_NAME}_BOARD nano)
set(ARDUINO_CPU atmega328old)
project(${PROJECT_NAME})

# Define additional source and header files or default arduino sketch files
set(${PROJECT_NAME}_SRCS busy_board.ino CRGBLED/CRGBLED.cpp CPlayer/CPlayer.cpp)
set(${PROJECT_NAME}_HDRS CRGBLED/CRGBLED.h CAnimalsGame/CAnimalsGame.h CColorsGame/CColorsGame.h CPlayer/CPlayer.h)

### Additional static libraries to include in the target.
# set(${PROJECT_NAME}_LIBS)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

### Main sketch file
set(${PROJECT_NAME}_SKETCH busy_board.ino)

### Add project directories into the build
# add_subdirectory()

### Additional settings to add non-standard or your own Arduino libraries.
# For this example (libs will contain additional arduino libraries)
# An Arduino library my_lib will contain files in libs/my_lib/: my_lib.h, my_lib.cpp + any other cpp files
link_directories(/home/shchuko/Arduino/libraries)

# For nested library sources replace ${LIB_NAME} with library name for each library
set(Keypad_RECURSE true)
set(DFMiniMp3_RECURSE true)
set(CRGBLED_RECURSE true)
set(CAnimalsGame_RECURSE true)
set(CRGBGame_RECURSE true)
set(EEPROM_RECURSE true)
set(CPlayer_RECURSE true)

#### Additional settings for programmer. From programmers.txt
set(${PROJECT_NAME}_PROGRAMMER avrisp)
set(${PROJECT_NAME}_PORT /dev/ttyUSB0)
# set(nano.upload.speed 9600)

## Verbose build process
# set(${PROJECT_NAME}_AFLAGS -v)
set(_RECURSE true)

generate_arduino_firmware(${PROJECT_NAME})
