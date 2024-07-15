#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Casino.h"

SDL_Window *window;
SDL_Renderer *renderer;

Casino* casino;

std::vector<std::string> symbol_names = {
    "bat", "big slime", "cactus monster", "cockatrice", "crab",
    "crocodile", "cumulus", "djinn", "dryad", "elder kappa",
    "fairy", "fluffy bear", "fox", "kobold", "mimic", "mining rat",
    "mushroom monster", "raven", "reaper", "red imp", "rhinoceros",
    "salamander", "shark", "sheep", "skeleton mage", "skeleton swordfighter",
    "spirit", "tengu", "tentacle monster", "tiger", "whispering wisp", "wolf"
};
std::vector<std::vector<int>> pay_lines = {
    {2, 2, 2, 2, 2}, {1, 1, 1, 1, 1},
    {3, 3, 3, 3, 3}, {1, 2, 3, 2, 1},
    {3, 2, 1, 2, 3}, {2, 1, 2, 1, 2},
    {2, 3, 2, 3, 2}, {1, 1, 2, 3, 3},
    {3, 3, 2, 1, 1}, {1, 3, 2, 1, 2},
    {1, 2, 1, 3, 2}, {1, 2, 2, 2, 1},
    {3, 2, 2, 2, 3}, {1, 2, 1, 2, 1},
    {3, 2, 3, 2, 3}, {2, 2, 1, 2, 2},
    {2, 2, 3, 2, 2}, {1, 1, 3, 1, 1},
    {3, 3, 1, 3, 3}, {1, 3, 3, 3, 1}
};

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    window = SDL_CreateWindow("Monster Casino", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
    renderer = SDL_CreateRenderer(window, 0, 0);

    casino = new Casino(renderer, symbol_names, pay_lines);

    while (casino->running) {
        SDL_Event e;


        if (SDL_QuitRequested()) {
            casino->running = false;
            break;
        }
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                casino->running = false;
                break;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
		                casino->current_screen = (casino->current_screen == 2 ? 0 : 2);
                        break;
                    default:
                        break;
                }
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                casino->handle_click(x, y);

            }
        }
        casino->render();
    }

    delete casino;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
