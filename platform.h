#ifndef PLATFORM_H
#define PLATFORM_H

#include "graphs.h"
#include <SDL.h>

class Platform {
public:
    Platform(const char* filename, SDL_Renderer* ren, int x, int y, int w, int h);
    void render();

    SDL_Rect getRect() { return destR; } // Lấy vị trí nền tảng để kiểm tra va chạm

private:
    SDL_Texture* texture;
    SDL_Rect srcR, destR;
    SDL_Renderer* renderer;
};

#endif
