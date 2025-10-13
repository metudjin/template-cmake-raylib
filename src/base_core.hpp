#ifndef BASE_CORE_HPP
#define BASE_CORE_HPP

#include "app_includes.hpp"


class BaseCore
{
public:
    BaseCore() = default;
    ~BaseCore() = default;

    // DPI scaling functions
    // Use these to scale any hardcoded values to the native display resolution
    float ScaleToDPIF(float value);     // Scale with float
    int ScaleToDPII(int value);         // Scale with int

    static inline const std::string assets_path{ASSETS_PATH};


};


#endif // BASE_CORE_HPP