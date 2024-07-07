#include "Casino.h"

Casino::Casino(SDL_Renderer *_renderer, std::vector<std::string> &symbol_names, const std::vector<std::vector<int>> &lines) {
    running = true;
    renderer = _renderer;
    pay_lines = lines;

    background_image = TextureManger::loadTexture(renderer, "assets/bg.png");

    int id = 0;
    for (auto &name : symbol_names) {
        std::string filename = "assets/sprites/";
        filename += name;
        filename += ".png";
        symbols.push_back({TextureManger::loadTexture(renderer, filename.c_str()), id});
        id++;
    }
    width = 5;
    height = 32;

    // Background source rectangle
    image_srcRect.w = 1280;
    image_srcRect.h = 720;
    image_srcRect.x = 0;
    image_srcRect.y = 0;

    image_destRect.w = 1280;
    image_destRect.h = 720;
    image_destRect.x = 0;
    image_destRect.y = 0;

    current_screen = 0;

    init_reels();
    buttons.push_back({520, 205, 240, 60});
    buttons.push_back({510, 300, 260, 60});
    buttons.push_back({10, 20, 180, 50});
    buttons.push_back({585, 390, 120, 60});
    buttons.push_back({1220, 30, 35, 35});
    buttons.push_back({110, 610, 90, 0});

}
Casino::~Casino() {
    for (auto &symbol : symbols)
        SDL_DestroyTexture(symbol.texture);
    SDL_DestroyTexture(background_image);
}

void Casino::init_reels() {
    int id = 0;
    for (int i = 0; i < 3; i++) {
        std::vector<Symbol> reel(5, symbols[id]);
        reels.push_back(reel);
        id++;
    }
}

void Casino::spin_reels() {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 5; c++) {
            reels[r][c] = symbols[randomNumberGenerator(height-1)];
        }
    }
    spin_animation();
}

int Casino::evaluate_pay_lines(int bet) {
    int multiplier = -1;
    for (int i = 0; i < 20; i++) {
        int type = reels[0][pay_lines[i][0] - 1].id;
        bool flag = true;
        for (int j = 1; j < 5; j++) {
            if (reels[j][pay_lines[i][j] - 1].id != type) {
                flag = false;
                break;
            }
        }
        if (flag) {
            multiplier = 20 - i;
            winning_line = pay_lines[i];
            break;
        }
    }
    return bet * multiplier;
}

void Casino::render() {
    SDL_RenderClear(renderer);

    image_srcRect.x = current_screen * (1320);
    TextureManger::Draw(renderer, background_image, image_srcRect, image_destRect);

    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // SDL_RenderDrawRect(renderer, &buttons[menu_button]);

    //SDL_RenderDrawLine(renderer, buttons[spin_button].x - buttons[spin_button].w, buttons[spin_button].y , buttons[spin_button].x + buttons[spin_button].w, buttons[spin_button].y);
    //SDL_RenderDrawLine(renderer, buttons[spin_button].x, buttons[spin_button].y  - buttons[spin_button].w, buttons[spin_button].x, buttons[spin_button].y + buttons[spin_button].w);

    SDL_RenderPresent(renderer);
}


void Casino::spin_animation() {
    // TODO: add spinning animation
}

void Casino::handle_click(int x, int y) {
    if (current_screen == 2) {
        if (x >= buttons[continue_button].x && x <= buttons[continue_button].x + buttons[continue_button].w && y >= buttons[continue_button].y && y <= buttons[continue_button].y + buttons[continue_button].h)
            current_screen = 0;
        else if (x >= buttons[pay_lines_button].x && x <= buttons[pay_lines_button].x + buttons[pay_lines_button].w && y >= buttons[pay_lines_button].y && y <= buttons[pay_lines_button].y + buttons[pay_lines_button].h)
            current_screen = 1;
        else if (x >= buttons[exit_button].x && x <= buttons[exit_button].x + buttons[exit_button].w && y >= buttons[exit_button].y && y <= buttons[exit_button].y + buttons[exit_button].h)
            running = false;
    } else if (current_screen == 1) {
        if (x >= buttons[go_back_button].x && x <= buttons[go_back_button].x + buttons[go_back_button].w && y >= buttons[go_back_button].y && y <= buttons[go_back_button].y + buttons[go_back_button].h)
            current_screen = 2;
    } else if (current_screen == 0) {
        if (x >= buttons[menu_button].x && x <= buttons[menu_button].x + buttons[menu_button].w && y >= buttons[menu_button].y && y <= buttons[menu_button].y + buttons[menu_button].h)
            current_screen = 2;
        else if (
            abs(x - buttons[spin_button].x) <= buttons[spin_button].w &&
            abs(y - buttons[spin_button].y) <= buttons[spin_button].w &&
            abs(x - buttons[spin_button].x) + abs(y  - buttons[spin_button].y <= buttons[spin_button].w)
            )
            std::cout << "spin\n";
    }
}
