#ifndef _GAMEFT__H
#define _GAMEFT__H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "graphs.h"
using namespace std;

class game{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    void init(const char* title, int x, int y, int width, int height, bool fullscreen);
    void renderTexture(SDL_Texture *texture, int x, int y, int w, int h, SDL_Renderer* renderer);
    void changes();
    void render();
    void quit();
    bool isRunnin;
    void update();
};

#endif // _GAMEFT__H
