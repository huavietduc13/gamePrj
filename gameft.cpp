#include "gameft.h"
#include "player.h"
#include "platform.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include "font.h"
#include "score.h"

Player* player;
std::vector<Platform*> platforms;
std::vector<SDL_Rect> boosters;
int maxHeightReached = 500;
bool isBoosted = 0;
int platformGenHeight;

void game::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
    isRunnin = true;
    srand((unsigned)time(nullptr));
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        isRunnin = false;
        std::cout << "ERROR!";
    } else {
        int fs = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
        window = SDL_CreateWindow(title, x, y, width, height, fs);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }

    TTF_Init();

    player = new Player(renderer, 200, 500);
    platformGenHeight = 500;

    background = IMG_LoadTexture(renderer, "img/back1.png");
    Sound::init();
    Sound::load();
    ScoreManager::Init();

    speakerOnTex = IMG_LoadTexture(renderer, "img/speaker_on.png");
    speakerOffTex = IMG_LoadTexture(renderer, "img/speaker_off.png");
    speakerRect = { 10, 10, 32, 32 };
    Mix_Volume(-1, volume);
}

void game::update() {
    if (isInMenu || isGameOver || isPaused) return;

    player->update();

    int targetY = player->getY() - 200;
    if (targetY < cameraY) cameraY -= (cameraY - targetY) / 10;
    if (cameraY > 0) cameraY = 0;

    while (player->getY() - 400 < platformGenHeight) {
        int px = rand() % (1280 - 400);
        int py = platformGenHeight - 100;

        platforms.push_back(new Platform("img/platform.png", renderer, px, py, 100, 28));

        if (rand() % 5 == 0) {
            SDL_Rect booster = { px + 30 , py - 20, 40, 20 };
            boosters.push_back(booster);
        }

        platformGenHeight -= 100;
    }

    for (auto& platform : platforms) {
        SDL_Rect playerRect = { player->getX(), player->getY(), 64, 64 };
        SDL_Rect platformRect = platform->getRect();

        if (player->getY() + 64 - player->velocityY <= platformRect.y &&
            SDL_HasIntersection(&playerRect, &platformRect)) {
            player->setY(platformRect.y - 64);
            player->resetVelocity();
            player->allowJump();
        }
    }
    for (auto& booster : boosters) {
        SDL_Rect playerRect = { player->getX(), player->getY(), 64, 64 };

        for (auto it = boosters.begin(); it != boosters.end(); ) {
            SDL_Rect booster = *it;
            if (SDL_HasIntersection(&playerRect, &booster)) {
                isBoosted = 1;
                it = boosters.erase(it);
                Sound::playBoost();
            } else {
                ++it;
            }
        }

        player->jumpForce = isBoosted ? -50 : -25;
    }

    platforms.erase(
        std::remove_if(platforms.begin(), platforms.end(),
            [this](Platform* p) {
                if (p->getRect().y - cameraY > 720) {
                    delete p;
                    return true;
                }
                return false;
            }),
        platforms.end());

    boosters.erase(
        std::remove_if(boosters.begin(), boosters.end(),
            [this](SDL_Rect& b) {
                return b.y - cameraY > 720;
            }),
        boosters.end());

    if (player->getY() - cameraY > 720) {
        isGameOver = true;
        ScoreManager::SaveHighScore();
        Sound::playGameOver();
        return;
    }

    ScoreManager::UpdateScore(player->getY());
}

void game::changes() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int mx = e.button.x;
                    int my = e.button.y;
                    if (mx >= speakerRect.x && mx <= speakerRect.x + speakerRect.w &&
                        my >= speakerRect.y && my <= speakerRect.y + speakerRect.h) {
                        isMuted = !isMuted;
                        Mix_Volume(-1, isMuted ? 0 : volume);
                    }
                }
                break;

            case SDL_MOUSEWHEEL:
                if (!isMuted) {
                    volume += e.wheel.y * 8;
                    volume = std::max(0, std::min(volume, MIX_MAX_VOLUME));
                    Mix_Volume(-1, volume);
                }
                break;

            case SDL_QUIT:
                isRunnin = false;
                break;
            case SDL_KEYDOWN:
                if (!isInMenu && !isGameOver && e.key.keysym.sym == SDLK_p) {
                    isPaused = !isPaused;
                }

                if (isInMenu && e.key.keysym.sym == SDLK_SPACE) {
                    isInMenu = false;
                    return;
                }
                if (isGameOver) {
                    if (e.key.keysym.sym == SDLK_r) {
                        ScoreManager::Reset();
                        maxHeightReached = 500;
                        Mix_HaltChannel(-1);
                        delete player;
                        for (auto p : platforms) delete p;
                        platforms.clear();
                        boosters.clear();
                        player = new Player(renderer, 200, 500);
                        platformGenHeight = 500;
                        cameraY = 0;
                        isGameOver = false;
                        return;
                    }
                    if (e.key.keysym.sym == SDLK_m) {
                        maxHeightReached = 500;
                        Mix_HaltChannel(-1);
                        isInMenu = true;
                        delete player;
                        for (auto p : platforms) delete p;
                        platforms.clear();
                        boosters.clear();
                        player = new Player(renderer, 200, 500);
                        platformGenHeight = 500;
                        cameraY = 0;
                        ScoreManager::Reset();
                        isGameOver = false;
                    }
                    break;
                }
                if (e.key.keysym.sym == SDLK_SPACE) {
                    bool wasJumping = player->isJumping;
                    player->jump();
                    if (!wasJumping && player->isJumping) {
                        Sound::playJump();
                        isBoosted = 0;
                    }
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
                if (!isGameOver && (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT)) {
                    player->stop();
                }
                break;
        }
    }
}

void game::render() {

    int barMaxWidth = 100;
    int barHeight = 10;
    int barX = speakerRect.x + speakerRect.w + 10;
    int barY = speakerRect.y + (speakerRect.h - barHeight) / 2;
    int filledWidth = isMuted ? 0 : (volume * barMaxWidth / MIX_MAX_VOLUME);

    if (isInMenu) {
        SDL_RenderClear(renderer);

        SDL_Rect bgRect = { 0, 0, 1280, 720 };
        SDL_RenderCopy(renderer, background, nullptr, &bgRect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        TTF_Font* titleFont = FontManager::LoadFont("font.ttf", 72);
        TTF_Font* infoFont = FontManager::LoadFont("font.ttf", 32);

        if (titleFont) {
            SDL_Color white = {255, 255, 255, 255};
            FontManager::DrawTextCentered(renderer, titleFont, "JUMP KNIGHT", white, 1280, 250);
            TTF_CloseFont(titleFont);
        }

        if (infoFont) {
            SDL_Color gray = {180, 180, 180, 255};
            FontManager::DrawTextCentered(renderer, infoFont, "Press SPACE to Start", gray, 1280, 400);
            TTF_CloseFont(infoFont);
        }

        infoFont = FontManager::LoadFont("font.ttf", 24);
        if (infoFont) {
            SDL_Color black = {0, 0, 0, 255};
            FontManager::DrawTextCentered(renderer, infoFont, "Use LEFT and RIGHT to Move", black, 1280, 460);
            FontManager::DrawTextCentered(renderer, infoFont, "Space to Jump", black, 1280, 500);
            FontManager::DrawTextCentered(renderer, infoFont, "Eat red orb can jump higher", black, 1280, 540);
            FontManager::DrawTextCentered(renderer, infoFont, "Press P to Pause during game", black, 1280, 580);
            TTF_CloseFont(infoFont);
        }

        SDL_Texture* speakerTex = isMuted ? speakerOffTex : speakerOnTex;
        SDL_RenderCopy(renderer, speakerTex, nullptr, &speakerRect);

        SDL_Rect backgroundBar = { barX, barY, barMaxWidth, barHeight };
        SDL_Rect filledBar = { barX, barY, filledWidth, barHeight };

        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
        SDL_RenderFillRect(renderer, &backgroundBar);

        SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
        SDL_RenderFillRect(renderer, &filledBar);

        SDL_RenderPresent(renderer);
        return;
    }

    if (isGameOver) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        TTF_Font* font = FontManager::LoadFont("Creepster-Regular.ttf", 72);
        if (font) {
            SDL_Color red = {255, 0, 0, 255};
            FontManager::DrawTextCentered(renderer, font, "GAME OVER", red, 1280, 300);
            TTF_CloseFont(font);
        }

        TTF_Font* smallFont = FontManager::LoadFont("Creepster-Regular.ttf", 32);
        if (smallFont) {
            SDL_Color gray = {200, 200, 200, 255};
            FontManager::DrawTextCentered(renderer, smallFont, "Press R to Restart", gray, 1280, 380);
            TTF_CloseFont(smallFont);
        }

        TTF_Font* smallFont1 = FontManager::LoadFont("font.ttf", 32);
        if (smallFont1) {
            SDL_Color gray = {200, 200, 200, 255};
            FontManager::DrawText(renderer, smallFont1, "Or press M to go to Menu", gray, 10, 680);
            TTF_CloseFont(smallFont1);
        }

        SDL_RenderPresent(renderer);
        return;
    }

    SDL_RenderClear(renderer);
    SDL_Rect bgRect = { 0, 0, 1280, 720 };
    SDL_RenderCopy(renderer, background, nullptr, &bgRect);

    SDL_Rect playerRect = player->getDestRect();
    playerRect.y -= cameraY;
    player->render(cameraY);

    for (Platform* platform : platforms) {
        SDL_Rect platformRect = platform->getRect();
        platformRect.y -= cameraY;
        SDL_RenderCopy(renderer, platform->getTexture(), nullptr, &platformRect);
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (auto& booster : boosters) {
        SDL_Rect boosted = booster;
        boosted.y -= cameraY;
        SDL_RenderFillRect(renderer, &boosted);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    TTF_Font* scoretext = FontManager::LoadFont("font.ttf", 24);
    int score = ScoreManager::GetScore();
    int highScore = ScoreManager::GetHighScore();
    if (scoretext) {
        SDL_Color black = {0, 0, 0, 255};
        std::string scoreText = "Score: " + std::to_string(score);
        FontManager::DrawText(renderer, scoretext, scoreText, black, 1000, 10);

        std::string highScoreText = "High Score: " + std::to_string(highScore);
        FontManager::DrawText(renderer, scoretext, highScoreText, black, 1000, 40);

        TTF_CloseFont(scoretext);
    }

    SDL_Texture* speakerTex = isMuted ? speakerOffTex : speakerOnTex;
    SDL_RenderCopy(renderer, speakerTex, nullptr, &speakerRect);

    SDL_Rect backgroundBar = { barX, barY, barMaxWidth, barHeight };
    SDL_Rect filledBar = { barX, barY, filledWidth, barHeight };

    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_RenderFillRect(renderer, &backgroundBar);

    SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
    SDL_RenderFillRect(renderer, &filledBar);

    if (isPaused) {
        TTF_Font* pauseFont = FontManager::LoadFont("font.ttf", 48);
        if (pauseFont) {
            SDL_Color yellow = {255, 255, 0, 255};
            FontManager::DrawTextCentered(renderer, pauseFont, "PAUSED", yellow, 1280, 360);
            TTF_CloseFont(pauseFont);
        }
    }

    SDL_RenderPresent(renderer);
}

void game::quit() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    delete player;
    for (auto& platform : platforms) {
        delete platform;
    }
    platforms.clear();
    boosters.clear();
    SDL_DestroyTexture(background);

    TTF_Quit();
    SDL_Quit();
    Sound::clean();
    SDL_DestroyTexture(speakerOnTex);
    SDL_DestroyTexture(speakerOffTex);
}
