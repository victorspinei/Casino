#include "TextureManager.h"

SDL_Texture* TextureManger::loadTexture(SDL_Renderer* renderer, const char* fileName)
{
    SDL_Surface* loadedSurface = IMG_Load(fileName);
    if (loadedSurface == nullptr) {
        SDL_Log("Failed to load image %s: %s\n", fileName, IMG_GetError());
        return nullptr;
    }
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (texture == nullptr) {
        SDL_Log("Failed to create texture from %s: %s\n", fileName, SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
    return texture;
}

void TextureManger::Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(renderer, texture, &src, &dest);
}
