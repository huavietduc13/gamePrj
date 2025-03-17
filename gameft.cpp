#include "gameft.h"

SDL_Texture* playerTex;

void game::renderTexture(SDL_Texture *texture, int x, int y, int w, int h, SDL_Renderer* renderer){
    SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.h = h;
	dest.w = w;
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

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

    SDL_Surface* tmpSurface = IMG_Load("img/player.png");
    playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

}

void game::changes(){
    SDL_Event e;
    SDL_PollEvent(&e);
    switch(e.type){
    case SDL_QUIT:
        isRunnin = 0;
        break;
    case SDL_KEYDOWN:
        isRunnin = 0;
        break;
    default:
        break;
    }
}

void game::render(){
    SDL_RenderClear(renderer);

    game::renderTexture(playerTex, 0, 0, 800, 600, renderer);

    SDL_RenderPresent(renderer);
}

void game::quit(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
