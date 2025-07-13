#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL2/SDL.h>
class Display {
    public:
        const static uint8_t DISPLAY_WIDTH{64};
        const static uint8_t DISPLAY_HEIGHT{32};

        enum Color {
            WHITE,
            BLACK
        } ;

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        bool display_arr[DISPLAY_WIDTH][DISPLAY_HEIGHT]{false};
        
    

        Display();
       void draw(int x_coord, int y_coord, Color color); 
};


#endif