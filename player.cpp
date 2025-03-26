#include "player.h"

player::player(const char* filename, SDL_Renderer* ren, int x, int y){
    xpos = x;
    ypos = y;
    renderer = ren;
    objTex = graphs::LoadTexture(filename, renderer);
}

void player::update(){
    vY += gravity;
    ypos += vY;

    if (ypos > 500) {
        ypos = 500;
        isJumping = false;
    }

    srcR.h = 128;
    srcR.w = 128;
    srcR.x = 0;
    srcR.y = 0;

    destR.h = 64;
    destR.w = 64;
    destR.x = xpos;
    destR.y = ypos;
}

void player::jump() {
    if (!isJumping) {
        vY = jumpForce;
        isJumping = 1;
    }
}

void player::render(){
    SDL_RenderCopy(renderer, objTex, &srcR, &destR);
}
