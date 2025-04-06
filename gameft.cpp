#include "gameft.h"
#include "player.h"
#include "platform.h"
#include <vector>

Player* player;
std::vector<Platform*> platforms;

void game::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
    isRunnin = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        isRunnin = false;
        std::cout << "ERROR!";
    } else {
        int fs = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
        window = SDL_CreateWindow(title, x, y, width, height, fs);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }

    player = new Player("img/player.png", renderer, 200, 500);

    platforms.push_back(new Platform("img/grass.png", renderer, 150, 550, 200, 30));
    platforms.push_back(new Platform("img/platform.png", renderer, 400, 450, 200, 30));
    platforms.push_back(new Platform("img/platform.png", renderer, 600, 350, 200, 30));
}

void game::update() {
    player->update();

    if (player->getY() < cameraY + 200) {
        cameraY = player->getY() - 200;
    }
    if (cameraY > 0) cameraY = 0; // Không để camera di chuyển xuống dưới nhân vật

    // Kiểm tra va chạm giữa nhân vật và nền tảng
    for (auto& platform : platforms) {
        SDL_Rect playerRect = { player->getX(), player->getY(), 64, 64 };
        SDL_Rect platformRect = platform->getRect();

        if (SDL_HasIntersection(&playerRect, &platformRect)) {
            player->setY(platformRect.y - 64); // Đặt nhân vật đứng trên nền tảng
            player->resetVelocity(); // Đặt lại vận tốc rơi
        }
    }

}

void game::changes() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                isRunnin = false;
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_SPACE) {
                    player->jump();
                }
                if (e.key.keysym.sym == SDLK_LEFT) {
                    player->moveLeft();
                }
                if (e.key.keysym.sym == SDLK_RIGHT) {
                    player->moveRight();
                }
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    game::quit();
                }
                break;
            case SDL_KEYUP:
                if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT) {
                    player->stop();
                }
                break;
        }
    }
}

void game::render() {
    SDL_RenderClear(renderer);

    SDL_Rect playerRect = player->getDestRect();
    playerRect.y -= cameraY; // Dịch theo camera
    SDL_RenderCopy(renderer, player->getTexture(), nullptr, &playerRect);

    for (Platform* platform : platforms) {
        SDL_Rect platformRect = platform->getRect();
        platformRect.y -= cameraY; // Dịch theo camera
        SDL_RenderCopy(renderer, platform->getTexture(), nullptr, &platformRect);
    }

    SDL_RenderPresent(renderer);
}

void game::quit(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
