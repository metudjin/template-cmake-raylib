#include "base_core.hpp"





float BaseCore::ScaleToDPIF(float value)        // Scale with float
{
    return GetWindowScaleDPI().x * value;
}

int BaseCore::ScaleToDPII(int value)            // Scale with int
{
    return int(GetWindowScaleDPI().x * value);
}