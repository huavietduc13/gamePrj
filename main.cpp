#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "gameft.h"


using namespace std;

int main(int argc, char *argv[])
{
    game g;
    g.init("Hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    while(g.isRunnin){
        g.changes();
        g.render();
        g.update();
    }
    g.quit();
    return 0;
}
