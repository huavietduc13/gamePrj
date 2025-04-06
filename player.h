#ifndef PLAYER_H
#define PLAYER_H

#include "graphs.h"
#include <SDL.h>

class Player {
public:
    Player(const char* filename, SDL_Renderer* ren, int x, int y);

    void update();
    void render();
    void jump();
    void moveLeft();
    void moveRight();
    void stop();

    int getX() { return xpos; }
    int getY() { return ypos; }
    void setY(int y) { ypos = y; }
    void resetVelocity() { velocityY = 0; }

    SDL_Texture* getTexture() { return objTex; }
    SDL_Rect getDestRect() { return destR; }

private:
    int xpos, ypos;
    int velocityX, velocityY;
    const int gravity = 1;
    const int jumpForce = -15;
    const int speed = 3;
    bool isJumping;

    SDL_Texture* objTex;
    SDL_Rect srcR, destR;
    SDL_Renderer* renderer;
};

#endif
