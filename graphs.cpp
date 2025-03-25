#include "graphs.h"

SDL_Texture* graphs::LoadTexture(const char* filename, SDL_Renderer* renderer){
    SDL_Surface* texSurf = IMG_Load(filename);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, texSurf);
    SDL_FreeSurface(texSurf);
    return tex;
}
