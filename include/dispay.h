#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL2/SDL.h>
class Display {
    public:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        Display();
        
};


#endif