#include "gameft.h"
#include "player.h"

player* Player;

void game::init(const char* title, int x, int y, int width, int height, bool fullscreen){
    isRunnin = 1;
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        isRunnin = 0;
        cout << "ERROR!";
    }
    else{
    int fs = 0;
    if(fullscreen) fs = SDL_WINDOW_FULLSCREEN;

    window = SDL_CreateWindow(title, x, y, width, height, fs);
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer) SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
    Player = new object("img/player.png", renderer,25, 25);
}

void game::changes(){
    SDL_Event e;
    SDL_PollEvent(&e);
    switch(e.type){
    case SDL_QUIT:
        isRunnin = 0;
        break;
    case SDL_KEYDOWN:
        if(e.key.keysym.sym == SDLK_SPACE){
            Player.jump();                      // Bấm space thì nhảy
        }
        break;
    default:
        break;
    }
}

void game::update(){
    Player->update();
}

void game::render(){
    SDL_RenderClear(renderer);

    Player->render();

    SDL_RenderPresent(renderer);
}

void game::quit(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
