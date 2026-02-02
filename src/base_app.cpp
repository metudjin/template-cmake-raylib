#include "base_app.hpp"





float BaseApp::ScaleToDPIF(float value)        // Scale with float
{
    return GetWindowScaleDPI().x * value;
}

int BaseApp::ScaleToDPII(int value)            // Scale with int
{
    return int(GetWindowScaleDPI().x * value);
}