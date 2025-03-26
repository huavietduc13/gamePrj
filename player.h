#ifndef _PLAYER__H_
#define _PLAYER__H_



#include "gameft.h"
#include "graphs.h"

class object{
public:
    object(const char* filename, SDL_Renderer* ren, int x, int y);
    ~object();
    void render();
    void update();
private:
    int xpos,ypos;  // Vị trí
    int vY;   // Vận tốc theo trục Y
    const int gravity = 1; // Trọng lực
    const int jumpForce = -15; // Lực nhảy
    bool isJumping;
    SDL_Texture* objTex;
    SDL_Rect srcR, destR;
    SDL_Renderer* renderer;
};

#endif // _PLAYER__H_
