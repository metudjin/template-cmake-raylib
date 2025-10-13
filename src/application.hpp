#ifndef APPLICATION_HPP
#define APPLICATION_HPP
// https://www.raylib.com/cheatsheet/cheatsheet.html

#include "base_core.hpp"



class Application : public BaseCore
{
public:
    Application();  // Constructor
    ~Application(); // Destructor

    void Update();  // Update function for raylib
    void Draw();    // Draw function for raylib




    

};


#endif //APPLICATION_HPP