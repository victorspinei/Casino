#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Casino.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureManger {
public:
    static SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* fileName);
    static void Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};

#endif //TEXTUREMANAGER_H
