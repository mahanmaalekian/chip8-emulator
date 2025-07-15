#include "display.h"

Display::Display() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(DISPLAY_WIDTH*10, DISPLAY_HEIGHT*10, 0, &window, &renderer);
    SDL_RenderSetLogicalSize(renderer, 64, 32);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_RenderDrawPoint(renderer, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2);

    // SDL_RenderPresent(renderer);
    // SDL_Delay(10000);
}

void Display::draw() {
    for (int y{0}; y < DISPLAY_HEIGHT; ++y){
        for (int x{0}; x < DISPLAY_WIDTH; ++x)
        {
            bool pixel = display_arr[y][x];
            if (pixel ) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_RenderDrawPoint(renderer, x, y);
        }
        
    }
    SDL_RenderPresent(renderer);
    //only works if i render all

}

