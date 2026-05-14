#ifndef BASE_APP_HPP
#define BASE_APP_HPP

#include "app_includes.hpp"


class BaseApp
{
public:
    BaseApp() = default;
    ~BaseApp() = default;

    // DPI scaling functions
    // Use these to scale any hardcoded values to the native display resolution
    float ScaleToDPIF(float value);     // Scale with float
    int ScaleToDPII(int value);         // Scale with int



};


#endif // BASE_APP_HPP