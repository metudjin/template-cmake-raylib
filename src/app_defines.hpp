#ifndef APP_DEFINES_HPP
#define APP_DEFINES_HPP


// Sets the assets path
#ifndef ASSETS_PATH
    #if defined(PLATFORM_DESKTOP)
        #define ASSETS_PATH "../assets/"
    #elif defined(PLATFORM_WEB)
        #define ASSETS_PATH "./assets/"
    #else
        #define ASSETS_PATH "../assets/"
    #endif
#endif


#endif // APP_DEFINES_HPP