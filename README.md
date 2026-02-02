# template-cmake-raylib
This is a C++23 template with CMake and Ninja as build system.  
It fetches raylib from GitHub and attaches to the project.  


## Information

- The CMake minimum version is 3.31.
- The C++ Version is set to C++23.
- There is support for C++20 Modules.
- Most of the template is written in modern C++17 and above.

### File Structure
```text
Folder structure:
-----------------
- assets        (assets folder)
    - fonts     (put your fonts here)
    - sprites   (put your sprites and spritesheets here)
- cmake         (optional cmake files folder)
- docs          (put documents that is for the application/game here)
- external      (sources from external libraries, you can call them with FetchContent in CMakeLists.txt)
- res           (resource folder)
    - html      (folder with .html for WASM export)
- search        (contains predefined searches in VS Code)
- src           (all the source code goes in here)
    - app_constants.hpp (Holds defined constants)
    - app_defines.hpp   (Holds defined values and strings)
    - app_includes.hpp  (Holds all the includes that is passed on to base_app.hpp)
    - application.hpp   (Application Declarations GAME CODE GOES HERE)
    - application.cpp   (Aplpication Implementations GAME CODE GOES HERE)
    - base_app.hpp      (Base App Declaration)
    - base_app.cpp      (Base App Implementation)
    - main.cpp          (This starts the Application)
```
Put all your starter game code in Application.hpp and Application.cpp.



## How To Begin


## Windows Install Dependencies
- Download and install [MSYS2](https://www.msys2.org/)
- [MSYS2 - Environments](https://www.msys2.org/docs/environments/)

### Install MSYS2 - UCRT64
```text
pacman -S mingw-w64-ucrt-x86_64-gcc
gcc --version
pacman -S mingw-w64-ucrt-x86_64-cmake
pacman -S mingw-w64-ucrt-x86_64-ninja
pacman -S mingw-w64-ucrt-x86_64-glfw
```
- Add "C:\msys64\ucrt64\bin" to System PATH
- If you are not familiar with this search google for "Add Windows PATH Environment Variable"

### Update MSYS2
- [MSYS2 - Docs - Updating](https://www.msys2.org/docs/updating/)
```text
pacman -Suy
Press "Y"
pacman -Suy
Press "Y"
paccache -r
```




## Windows Install and configure Emscripten by downloading and activating EMSDK
### NOT COMPLETE!






## Linux Install Dependencies

- Check if GCC is installed otherwise install it.
- Install following packages in Debian/Ubuntu for use with X11 and X11 under Wayland
```bash
sudo apt update
sudo apt install build-essential
sudo apt install cmake ninja-build git pkg-config
sudo apt install xwayland libegl1-mesa-dev
sudo apt install libopengl0 libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev
sudo apt install libx11-dev libxi-dev libxinerama-dev libxcursor-dev libxrandr-dev
sudo apt install libasound2-dev libpulse-dev libudev-dev libdbus-1-dev
sudo apt install libglfw3 libglfw3-dev
sudo apt install libopenal-dev libsndfile1-dev libfreetype6-dev
```




## Linux Install and configure Emscripten by downloading and activating EMSDK

```bash
cd ~/
# Get the emsdk repo
git clone https://github.com/emscripten-core/emsdk.git

# Enter that directory
cd emsdk

# Fetch the latest version of the emsdk (not needed the first time you clone)
git pull

# Download and install the latest SDK tools.
./emsdk install latest

# Make the "latest" SDK "active" for the current user. (writes .emscripten file)
./emsdk activate latest

# Activate PATH and other environment variables in the current terminal
source ./emsdk_env.sh
```

- Add PATH to Environment permanently

```bash
### Next steps:
# - To conveniently access emsdk tools from the command line,
#   consider adding the following directories to your PATH:
#   /home/user/emsdk
#   /home/user/emsdk/upstream/emscripten
# - This can be done for the current shell by running:
#   source "/home/user/emsdk/emsdk_env.sh"
# - Configure emsdk in your shell startup scripts by running:
#   echo 'source "/home/user/emsdk/emsdk_env.sh"' >> $HOME/.bash_profile


### See if it works with temporary PATHs
user@user:~$ source "/home/user/emsdk/emsdk_env.sh"
Setting up EMSDK environment (suppress these messages with EMSDK_QUIET=1)
Adding directories to PATH:
PATH += /home/user/emsdk
PATH += /home/user/emsdk/upstream/emscripten

Setting environment variables:
PATH = /home/user/emsdk:/home/user/emsdk/upstream/emscripten:/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games:/snap/bin:/home/user/.dotnet/t>
EMSDK = /home/user/emsdk
EMSDK_NODE = /home/user/emsdk/node/20.18.0_64bit/bin/node


### Add to the bottom of .profile for permanent PATHs
# emsdk, added by user
export PATH="/home/user/emsdk/upstream/emscripten:$PATH"
export PATH="/home/user/emsdk:$PATH"
export EMSDK="/home/user/emsdk"
export EMSDK_NODE="/home/user/emsdk/node/22.16.0_64bit/bin/node"
# emsdk, use a script instead of adding PATH above, added by user
#export EMSDK_QUIET=1
#source "/home/user/emsdk/emsdk_env.sh"
```




## How To Copy a project (Visual Studio Code)
- Copy the template folder to a new location and name the folder the intended "Project name".
- Change the projectname in CMakeLists.txt project("Project name").
- Remove all cmake-build-xxx-xxx from the newly copied project.




## Links


### CPP References
- [CPP Reference](https://en.cppreference.com/)
- [CPP Reference - C](https://en.cppreference.com/w/c.html)
- [CPP Reference - C++](https://en.cppreference.com/w/cpp.html)


### raylib
- [raylib](https://www.raylib.com/)
- [GitHub - raylib (raysan5)](https://github.com/raysan5/raylib)
- [GitHub - raylib - wiki (raysan5)](https://github.com/raysan5/raylib/wiki)
- [GitHub - raylib - wiki - WebAssembly (raysan5)](https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5))


### GLFW
- [GLFW](https://www.glfw.org/)
- [GitHub - GLFW](https://github.com/glfw/glfw)


### Emscripten
- [Emscripten - Getting Started](https://emscripten.org/docs/getting_started/index.html)
- [Emscripten - Browser main loop](https://emscripten.org/docs/porting/emscripten-runtime-environment.html#browser-main-loop)
- [GitHub - EMSDK (Emscripten-core)](https://github.com/emscripten-core/emsdk)


### CMake
- [CMake - Help](https://cmake.org/cmake/help/latest/)
- [CMake - Help - CMake Commands](https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html)
- [CMake - Help - CMake Variables](https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html)


### Visual Studio Code
- [Visual Studio Code](https://code.visualstudio.com/)
- [Visual Studio Code - Documentation](https://code.visualstudio.com/docs/)
- [Visual Studio Code - MinGW](https://code.visualstudio.com/docs/cpp/config-mingw)
- [Visual Studio Code - Variable References](https://code.visualstudio.com/docs/editor/variables-reference)


### MSYS2
- [MSYS2](https://www.msys2.org/)
- [MSYS2 - Packages](https://packages.msys2.org/)
- [MSYS2 - CMake in MSYS2](https://www.msys2.org/docs/cmake/)
- [MSYS2 - Environments](https://www.msys2.org/docs/environments/)


### GIT
- [GitHub](https://github.com/)
- [GitHub Docs](https://docs.github.com/)


## EOF