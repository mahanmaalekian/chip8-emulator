#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL2/SDL.h>
class SystemInterface {
    public:
        const static uint8_t DISPLAY_WIDTH{64};
        const static uint8_t DISPLAY_HEIGHT{32};

        enum Color {
            WHITE,
            BLACK
        } ;

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        bool display_arr[DISPLAY_HEIGHT][DISPLAY_WIDTH]{false};
        bool keys[16]{false};
        
    

        SystemInterface();
        void draw_display(); 
        bool process_input();
};


#endif