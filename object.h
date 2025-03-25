#ifndef _OBJECT__H_
#define _OBJECT__H_

#include "gameft.h"
#include "graphs.h"

class object{
public:
    object(const char* filename, SDL_Renderer* ren, int x, int y);
    ~object();
    void render();
    void update();
private:
    int xpos,ypos;
    SDL_Texture* objTex;
    SDL_Rect srcR, destR;
    SDL_Renderer* renderer;
};

#endif // _OBJECT__H_
