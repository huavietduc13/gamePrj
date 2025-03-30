
#include "platform.h"

Platform::Platform(const char* filename, SDL_Renderer* ren, int x, int y, int w, int h) {
    renderer = ren;
    texture = graphs::LoadTexture(filename, renderer);

    srcR = { 0, 0, 128, 128 }; // Kích thước ảnh gốc
    destR = { x, y, w, h }; // Kích thước thực tế trên màn hình
}

void Platform::render() {
    SDL_RenderCopy(renderer, texture, &srcR, &destR);
}
