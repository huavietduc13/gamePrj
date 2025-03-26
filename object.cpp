#include "object.h"

object::object(const char* filename, SDL_Renderer* ren, int x, int y){
    xpos = x;
    ypos = y;
    renderer = ren;
    objTex = graphs::LoadTexture(filename, renderer);
}

void object::update(){
    srcR.h = 128;
    srcR.w = 128;
    srcR.x = 0;
    srcR.y = 0;

    destR.h = 64;
    destR.w = 64;
    destR.x = xpos;
    destR.y = ypos;
}

void object::render(){
    SDL_RenderCopy(renderer, objTex, &srcR, &destR);
}
