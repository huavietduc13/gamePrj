#include "player.h"

Player::Player(const char* filename, SDL_Renderer* ren, int x, int y) {
    xpos = x;
    ypos = y;
    velocityY = 0;
    isJumping = false;
    renderer = ren;
    objTex = graphs::LoadTexture(filename, renderer);
}

void Player::update() {
    velocityY += gravity;
    ypos += velocityY;

    if (ypos > 500) {
        ypos = 500;
        isJumping = false;
    }

    srcR = { 0, 0, 128, 128 };
    destR = { xpos, ypos, 64, 64 };
}

void Player::jump() {
    if (!isJumping) {
        velocityY = jumpForce;
        isJumping = true;
    }
}

void Player::render() {
    SDL_RenderCopy(renderer, objTex, &srcR, &destR);
}
