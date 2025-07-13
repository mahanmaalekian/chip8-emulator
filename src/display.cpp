#include "display.h"

Display::Display() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 4, 4);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoint(renderer, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2);

    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
}

void Display::draw(int x_coord, int y_coord, Color color) {
    if (color == WHITE){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
    SDL_RenderDrawPoint(renderer, x_coord, y_coord);
}