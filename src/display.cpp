#include "dispay.h"

Display::Display() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(640*4, 480*4, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 4, 4);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoint(renderer, 640/2, 480/2);

    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
}