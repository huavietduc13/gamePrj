#ifndef _GAMEFT__H
#define _GAMEFT__H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include "graphs.h"
#include "sound.h"

using namespace std;

class game{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *background;
    SDL_Texture* speakerOnTex;
    SDL_Texture* speakerOffTex;
    SDL_Rect speakerRect;
    bool isMuted = false;
    int volume = MIX_MAX_VOLUME;

public:
    int cameraY = 0;
    void init(const char* title, int x, int y, int width, int height, bool fullscreen);
    void renderTexture(SDL_Texture *texture, int x, int y, int w, int h, SDL_Renderer* renderer);
    void changes();
    void render();
    void quit();
    bool isRunnin;
    void update();
};

#endif // _GAMEFT__H
