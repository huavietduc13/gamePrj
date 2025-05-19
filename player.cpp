#include "player.h"

Player::Player(SDL_Renderer* ren, int x, int y) {
    xpos = x;
    ypos = y;
    velocityX = 0;
    velocityY = 0;
    isJumping = false;
    renderer = ren;

    runTexture = graphs::LoadTexture("img/player_run.png", renderer);
    jumpTexture = graphs::LoadTexture("img/player_jump.png", renderer);
    idleTexture = graphs::LoadTexture("img/player_idle.png", renderer);

    srcR = { 0, 0, 128, 128 };
    destR = { xpos, ypos, 64, 64 };
}

void Player::update() {
    velocityY += gravity;
    xpos += velocityX;
    ypos += velocityY;

    if (velocityX < 0) facingLeft = true;
    if (velocityX > 0) facingLeft = false;

    if (ypos > 500) {
        ypos = 500;
        isJumping = false;
    }

    if (!isJumping && velocityX != 0) {
        frameTick++;
        if (frameTick >= frameDelay) {
            frameTick = 0;
            runFrame = (runFrame + 1) % frameCount;
        }
        srcR = { 128 * runFrame, 0, 128, 128 };
    } else {
        srcR = { 0, 0, 128, 128 };
    }

    destR = { xpos, ypos, 64, 64 };
}

void Player::jump() {
    if (!isJumping) {
        velocityY = jumpForce;
        isJumping = true;
    }
}

void Player::moveLeft() {
    velocityX = -speed;
}

void Player::moveRight() {
    velocityX = speed;
}

void Player::stop() {
    velocityX = 0;
}

void Player::render(int cameraY) {
    SDL_Texture* currentTex;

    if (isJumping)
        currentTex = jumpTexture;
    else if (velocityX == 0)
        currentTex = idleTexture;
    else
        currentTex = runTexture;

    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    SDL_Rect renderRect = destR;
    renderRect.y -= cameraY;

    SDL_RenderCopyEx(renderer, currentTex, &srcR, &renderRect, 0, nullptr, flip);
}

void Player::allowJump() {
    isJumping = false;
}

SDL_Texture* Player::getTexture() {
    return runTexture;
}

SDL_Rect Player::getDestRect() {
    return destR;
}
