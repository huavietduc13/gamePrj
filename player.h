#ifndef _PLAYER__H
#define _PLAYER__H

#include "graphs.h"
#include <SDL.h>

class Player {
public:
    Player(SDL_Renderer* ren, int x, int y);

    void update();
    void render(int cameraY);
    void jump();
    void moveLeft();
    void moveRight();
    void stop();

    int getX() { return xpos; }
    int getY() { return ypos; }
    void setY(int y) { ypos = y; }
    void resetVelocity() { velocityY = 0; }

    SDL_Texture* getTexture();
    SDL_Rect getDestRect();

    int velocityY;
    bool isJumping;
    void allowJump();
    int jumpForce = -25;

private:
    int xpos, ypos;
    int velocityX;
    const int gravity = 1;
    const int speed = 5;

    SDL_Renderer* renderer;
    SDL_Rect srcR, destR;

    SDL_Texture* runTexture;
    SDL_Texture* jumpTexture;
    SDL_Texture* idleTexture;

    bool facingLeft = false;
    int runFrame = 0;
    int frameCount = 3;
    int frameDelay = 8;
    int frameTick = 0;
};

#endif // _PLAYER__H
