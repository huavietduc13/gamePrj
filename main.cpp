#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "gameft.h"

using namespace std;

int main(int argc, char *argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    game g;
    g.init("Jump Knight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    while(g.isRunnin){
        frameStart = SDL_GetTicks();
        g.changes();
        g.update();
        g.render();
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    g.quit();
    return 0;
}
