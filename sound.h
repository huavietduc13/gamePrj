#ifndef _SOUND__H_
#define _SOUND__H_

#include <SDL_mixer.h>
#include <string>

class Sound {
public:
    static void init();
    static void load();
    static void playJump();
    static void playBoost();
    static void playGameOver();
    static void clean();

private:
    static Mix_Chunk* jumpSound;
    static Mix_Chunk* boostSound;
    static Mix_Chunk* gameOverSound;
};

#endif // _SOUND__H_
