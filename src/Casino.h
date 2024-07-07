#ifndef CASINO_H
#define CASINO_H

#include "TextureManager.h"
#include <vector>
#include <utility>
#include <string>
#include <random>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

enum Buttons {
    continue_button,
    pay_lines_button,
    go_back_button,
    exit_button,
    menu_button,
    spin_button
};

typedef std::mt19937 rng_type;

inline int randomNumberGenerator(const int limit) {
    std::random_device rd;
    rng_type gen(rd());
    std::uniform_int_distribution<> dis(0, limit);
    return dis(gen);
}

struct Symbol {
    SDL_Texture *texture;
    int id;
};


class Casino {
public:
    Casino(SDL_Renderer *_renderer, std::vector<std::string> &symbol_names, const std::vector<std::vector<int>> &lines);
    ~Casino();

    void render();

    void spin_animation();

    void spin_reels();
    void init_reels();
    int evaluate_pay_lines(int bet);

    void handle_click(int x, int y);

    bool running;
    SDL_Renderer *renderer;

    int current_screen;
private:
    int width, height;

    SDL_Texture* background_image;

    SDL_Rect image_srcRect;
    SDL_Rect image_destRect;

    std::vector<SDL_Rect> buttons;


    std::vector<std::vector<Symbol>> reels;
    std::vector<Symbol> symbols;
    std::vector<std::vector<int>> pay_lines;
    std::vector<int> winning_line;

};


#endif //CASINO_H
