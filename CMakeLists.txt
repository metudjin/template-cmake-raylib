cmake_minimum_required(VERSION 3.31)
project(template_cmake_raylib)

set(CMAKE_CXX_STANDARD 23)              # Tries -std=c++23, if no exists compiler tries lower -std=c++20, -std=c++17 etc.
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Enforces the CXX_STANDARD version targeted above
set(CMAKE_CXX_EXTENSIONS OFF)           # Makes it more portable by disabling non-standard compiler extensions and flags
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # Creates "compile_commands.json" with all build commands
set(CMAKE_CXX_SCAN_FOR_MODULES ON)      # This handles the build order automatically for CXX Modules
set(CMAKE_VERBOSE_MAKEFILE ON)          # See the full commands when make is building the project, does not work with ninja.

#include(${CMAKE_SOURCE_DIR}/PreLoad.cmake)  # This file is included by default if its in the same dir as CMakeLists.txt
#include(${CMAKE_SOURCE_DIR}/cmake/Options.cmake)

#set(PLATFORM Desktop)           # Desktop, Web, Android, RPI, DRM, SDL (-DPLATFORM=Desktop as CMake identifier)
#set(PLATFORM Web)               # Web instead of (-DPLATFORM=Web as CMake identifier)
#set(PLATFORM_OS Linux)          # [Desktop] - Windows (Win32, Win64), Linux (X11/Wayland), OSX (x64, arm64), BSD (X11)
#set(CMAKE_BUILD_TYPE "Debug")   # Use if you dont want to set it via -DCMAKE_BUILD_TYPE=Debug on compile-time
#set(CMAKE_BUILD_TYPE "Release") # Use if you dont want to set it via -DCMAKE_BUILD_TYPE=Release on compile-time

set(ASYNCIFY OFF)               # Sets Asyncify on or off, used for WebGL loops


file(GLOB ALL_SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/*.hpp" "${CMAKE_SOURCE_DIR}/src/*.c" "${CMAKE_SOURCE_DIR}/src/*.h")
#file(GLOB_RECURSE ALL_SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/*.hpp" "${CMAKE_SOURCE_DIR}/src/*.c" "${CMAKE_SOURCE_DIR}/src/*.h")
message(STATUS "")
message(STATUS "")
message(STATUS "======== Found source and header files ========")
message(STATUS "${ALL_SRC_FILES}")
message(STATUS "===============================================")
message(STATUS "")


file(GLOB ALL_CXX_MODULE_FILES "${CMAKE_SOURCE_DIR}/src/*.cppm" "${CMAKE_SOURCE_DIR}/src/*.ixx" "${CMAKE_SOURCE_DIR}/src/*.mxx")
#file(GLOB_RECURSE ALL_CXX_MODULE_FILES "${CMAKE_SOURCE_DIR}/src/*.cppm" "${CMAKE_SOURCE_DIR}/src/*.ixx" "${CMAKE_SOURCE_DIR}/src/*.mxx")
message(STATUS "")
message(STATUS "")
message(STATUS "======== Found cxx module files ========")
message(STATUS "${ALL_CXX_MODULE_FILES}")
message(STATUS "========================================")
message(STATUS "")


set(MAIN_SRC_FILES
)

set(CLASS_SRC_FILES
)


### FetchContent
include(FetchContent)


### Begin FetchContent raylib
message(STATUS "")
message(STATUS "======== raylib FetchContent Begin ========")
set(RAYLIB_VERSION 5.5)
if (${PLATFORM} MATCHES "Desktop")
    #set(OPENGL_VERSION "4.3")       # OPENGL_VERSION "OFF;4.3;3.3;2.1;1.1;ES 2.0;ES 3.0"
endif()
if (${PLATFORM} MATCHES "Web")
    #set(OPENGL_VERSION "ES 3.0")    # OPENGL_VERSION "OFF;4.3;3.3;2.1;1.1;ES 2.0;ES 3.0"
endif()
#set(GLFW_BUILD_WAYLAND ON)
#set(GLFW_BUILD_X11 OFF)
#set(GLFW_LINUX_ENABLE_WAYLAND TRUE)
#set(INCLUDE_EVERYTHING OFF)
FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
        #URL ${CMAKE_SOURCE_DIR}/external/raylib/raylib-${RAYLIB_VERSION}.tar.gz        # Use this if you have a downloaded source of raylib
        FIND_PACKAGE_ARGS
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)
message(STATUS "======== raylib FetchContent End   ========")
### FetchContent builds raylib as a static lib because raylib has a CMakeLists.txt that is preconfigured for that.
### End FetchContent raylib


### Information (Advanced)
### 1. add_executable() - This creates the target so it has to be before target_include_directories, target_sources & target_link_libraries
### 2. target_include_directories() - This adds paths to directories with header files so the compiler finds header files need for linked libraries
### 3. target_sources() - This adds a folder to be built by the compiler
### 4. target_link_libraries() - This links a library
### 5. Add modules

add_executable(${PROJECT_NAME}
        ${ALL_SRC_FILES}
        ${MAIN_SRC_FILES}
        ${CLASS_SRC_FILES}
)

### target_include_directories()


### target_sources()


### target_link_libraries()
#target_link_libraries(${PROJECT_NAME} PRIVATE raylib)   # Added below in Windows, Linux and Web section


### CXX Modules (Only used if Modules are used in the program)
### If no modules are used these line below need to be commented out
target_sources(${PROJECT_NAME} PRIVATE FILE_SET cxx_modules TYPE CXX_MODULES FILES ${ALL_CXX_MODULE_FILES})


add_compile_definitions(PROJECT_PATH="${CMAKE_SOURCE_DIR}")


### Linux Compile With raylib

if (CMAKE_HOST_LINUX AND ${PLATFORM} MATCHES "Desktop")       # Use LINUX if compiling on Windows to target Linux
    add_compile_definitions(PLATFORM_DESKTOP)
    set(CMAKE_C_COMPILER gcc)           # MinGW
    set(CMAKE_CXX_COMPILER g++)         # MinGW

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)        # raylib

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/cmake-out/install/linux-debug")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wformat")
    endif ()

    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/cmake-out/install/linux-release")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1 -Wall")
    endif ()
endif ()




### Windows Compile With raylib

if (CMAKE_HOST_WIN32 AND ${PLATFORM} MATCHES "Desktop")       # Use WIN32 if compiling on Linux to target Windows
    add_compile_definitions(PLATFORM_DESKTOP)
    set(CMAKE_C_COMPILER gcc.exe)       # MinGW
    set(CMAKE_CXX_COMPILER g++.exe)     # MinGW

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib opengl32 gdi32 winmm)   # raylib

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/cmake-out/install/windows-debug")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wformat")
    endif ()

    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/cmake-out/install/windows-release")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1 -Wall")
    endif ()
endif ()




### WebAssembly Compile With raylib

if (CMAKE_HOST_LINUX AND ${PLATFORM} MATCHES "Web")
    add_compile_definitions(PLATFORM_WEB)           # raylib

    set(EMSDK_PATH $ENV{EMSDK})
    set(EMSCRIPTEN_PATH ${EMSDK_PATH}/upstream/emscripten)
    set(CLANG_PATH ${EMSDK_PATH}/upstream/bin)
    message(STATUS "")
    message(STATUS "======== Emscripten SDK information ========")
    message(STATUS "EMSDK PATH       : ${EMSDK_PATH}")
    message(STATUS "Emscripten PATH  : ${EMSCRIPTEN_PATH}")

    #set(CMAKE_TOOLCHAIN_FILE ${EMSCRIPTEN_PATH}/cmake/Modules/Platform/Emscripten.cmake)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(CMAKE_C_COMPILER emcc)      # Emscripten
    set(CMAKE_CXX_COMPILER em++)    # Emscripten

    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)       # raylib

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s GL_ENABLE_GET_PROC_ADDRESS=1")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1")
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --preload-file assets")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --shell-file ${CMAKE_SOURCE_DIR}/res/html/shell.html")

    if (ASYNCIFY MATCHES "ON")
        message(STATUS "ASYNCIFY: ON")
        message(STATUS "Use standard raylib while(!WindowShouldClose){} loop")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s ASYNCIFY")
    endif ()

    if (ASYNCIFY MATCHES "OFF")
        message(STATUS "ASYNCIFY: OFF")
        message(STATUS "Use emscripten_set_main_loop(UpdateDrawFrame, 0, 1);")
    endif ()

    if (ASYNCIFY MATCHES "ON" AND CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/cmake-out/install/web-release-asyncify")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    endif ()

    if (ASYNCIFY MATCHES "OFF" AND CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/cmake-out/install/web-release")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")
    endif ()

    if (ASYNCIFY MATCHES "ON" AND CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/cmake-out/install/web-debug-asyncify")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    endif ()

    if (ASYNCIFY MATCHES "OFF" AND CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/cmake-out/install/web-debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    endif ()

    ### Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable
    target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets/")
endif ()




### Messages
message(STATUS "")
message(STATUS "")
message(STATUS "======== Environment information ========")
message(STATUS "Host System         : ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "Host Architecture   : ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS "Target Platform     : ${PLATFORM}, ${CMAKE_HOST_SYSTEM_NAME}, ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS "Project Path        : ${CMAKE_SOURCE_DIR}")
message(STATUS "Current Folder Path : ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "")

get_target_property(LIST_OF_LINKED_LIBS ${PROJECT_NAME} LINK_LIBRARIES)
message(STATUS "C Compiler          : ${CMAKE_C_COMPILER}")
message(STATUS "CXX Compiler        : ${CMAKE_CXX_COMPILER}")
message(STATUS "C Flags             : ${CMAKE_C_FLAGS}")
message(STATUS "CXX Flags           : ${CMAKE_CXX_FLAGS}")
message(STATUS "Linker Flags        : ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "Linked Libraries    : ${LIST_OF_LINKED_LIBS}")
message(STATUS "")
message(STATUS "")


### ==============================================================================
### HELP
### ==============================================================================


# CXX Modules
# ==============================================================================
# CMake and JetBrains CLion only recognise .cppm, .ixx, .mxx as module files
# g++ -std=c++23 -fmodules-ts -x c++ module.cppm -c -o module.o
# g++ -std=c++23 -fmodules-ts main.cpp module.o -o app
# To use modules with C++ and CMake Ninja build is also needed


### raylib commandline compile help
# ==============================================================================
# To compile raylib game directly from the command line, those are the commands to run:
# NOTE: in /raylib/src/ there is a file called minshell.html which is the recommended shell file for Raylib applications.
# So you may pass --shell-file $HOME/raylib/src/minshell.html to emcc if you had Raylib in your home directory.

# Without ASYNCIFY
# emcc -o game.html game.c -Os -Wall ./path-to/libraylib.a -I. -Ipath-to-raylib-h -L. -Lpath-to-libraylib-a -s USE_GLFW=3 --shell-file path-to/shell.html -DPLATFORM_WEB

# With ASYNCIFY
# emcc -o game.html game.c -Os -Wall ./path-to/libraylib.a -I. -Ipath-to-raylib-h -L. -Lpath-to-libraylib-a -s USE_GLFW=3 -s ASYNCIFY --shell-file path-to/shell.html -DPLATFORM_WEB

# The compilation line is quite standard, similar to any other compiler and platform.
# Here a small explanation of the different parameters:
# ==============================================================================
#   -o game.html    // Output file, the .html extension determines the files that need to be generated: `.wasm`, `.js` (glue code) and `.html` (optional: `.data`). All files are already configured to just work.
#   game.c          // The input files for compilation, in this case just one but it could be multiple code files: `game.c screen_logo.c screen_title.c screen_gameplay.c`
#   -Os -Wall       // Some config parameters for the compiler, optimize code for small size and show all warnings generated
#   ./path-to/libraylib.a   // This is the libraylib.a generated, it's recommended to provide it directly, with the path to it: i.e. `./raylib/src/libraylib.a`
#   -Ipath          // Include path to look for additional #include .h files (if required)
#   -Lpath          // Library path to look for additional library .a files (if required)
#   -s USE_GLFW=3   // We tell the linker that the game/library uses GLFW3 library internally, it must be linked automatically (emscripten provides the implementation)
#   -s ASYNCIFY     // Add this flag ONLY in case we are using ASYNCIFY code
#   --shell-file path-to/shell.html  // All webs need a "shell" structure to load and run the game, by default emscripten has a `shell.html` but we can provide our own

# There are some additional emscripten flags that can be useful if the game requires them.
# For example, in case of resources loading (images, textures, audio, fonts, models..), they need to be compiled with code (.data file generated).
# Web games use an internal Virtual-File-System to store data.
# Also note that the maximum memory size required by the application (considering everything the game will load) SHOULD be provided.

# Here are some of those additional flags:
# ==============================================================================
#   --preload-file resources      // Specify a resources directory for data compilation (it will generate a .data file)
#   -s TOTAL_MEMORY=67108864      // Specify a heap memory size in bytes (default = 16MB) (67108864 = 64MB)
#   -s ALLOW_MEMORY_GROWTH=1      // Allow automatic heap memory resizing -> NOT RECOMMENDED!
#   -s FORCE_FILESYSTEM=1         // Force filesystem creation to load/save files data (for example if you need to support save-game or drag&drop files)
#   -s ASSERTIONS=1               // Enable runtime checks for common memory allocation errors (-O1 and above turn it off)
#   --profiling                   // Include information for code profiling


# External Information
# ==============================================================================
# Since WASM is used, ALLOW_MEMORY_GROWTH has no extra overheads


# Add to CLion "CMake options:" if not added in CMakeLists.txt
# ==============================================================================
# -DCMAKE_TOOLCHAIN_FILE=/home/fredrik/GitHub/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
# -DPLATFORM=Desktop
# -DPLATFORM=Web
# -DCMAKE_INSTALL_PREFIX="${CMAKE_SOURCE_DIR}/cmake-out/install/linux-debug"    # Change linux-debug to directory of choice
# -DCMAKE_C_COMPILER=gcc                                    # MinGW
# -DCMAKE_CXX_COMPILER=g++                                  # MinGW
# -DCMAKE_C_COMPILER=/usr/bin/gcc                           # MinGW
# -DCMAKE_CXX_COMPILER=/usr/bin/g++                         # MinGW
# -DCMAKE_BUILD_TYPE=Debug                                  # Change between Debug or Release

