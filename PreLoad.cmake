message(STATUS "")
message(STATUS "======== PreLoad.cmake - Begin ========")

if(CMAKE_HOST_WIN32)
    set(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "" FORCE)
    set(CMAKE_MAKE_PROGRAM "ninja.exe" CACHE PATH "Override the make program")
endif()

message(STATUS "======== PreLoad.cmake - End   ========")
message(STATUS "")