#include "gameft.h"
#include "player.h"
#include "platform.h"
#include <vector>

Player* player;
std::vector<Platform*> platforms;

void game::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
    isRunning = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        isRunning = false;
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

void game::render() {
    SDL_RenderClear(renderer);

    // Vẽ nền tảng
    for (auto& platform : platforms) {
        platform->render();
    }

    // Vẽ nhân vật
    player->render();

    SDL_RenderPresent(renderer);
}
