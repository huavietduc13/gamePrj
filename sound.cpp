#include "sound.h"

Mix_Chunk* Sound::jumpSound = nullptr;
Mix_Chunk* Sound::boostSound = nullptr;
Mix_Chunk* Sound::gameOverSound = nullptr;

void Sound::init() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void Sound::load() {
    jumpSound = Mix_LoadWAV("sound/jump.mp3");
    boostSound = Mix_LoadWAV("sound/boost.mp3");
    gameOverSound = Mix_LoadWAV("sound/gameover.mp3");
}

void Sound::playJump() {
    if (jumpSound) Mix_PlayChannel(-1, jumpSound, 0);
}

void Sound::playBoost() {
    if (boostSound) Mix_PlayChannel(-1, boostSound, 0);
}

void Sound::playGameOver() {
    if (gameOverSound) Mix_PlayChannel(-1, gameOverSound, 0);
}

void Sound::clean() {
    Mix_FreeChunk(jumpSound);
    Mix_FreeChunk(boostSound);
    Mix_FreeChunk(gameOverSound);
    Mix_CloseAudio();
}
