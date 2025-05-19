#ifndef _FONT__H_
#define _FONT__H_

#include <SDL_ttf.h>
#include <string>

class FontManager {
public:
    static TTF_Font* LoadFont(const std::string& file, int fontSize) {
        TTF_Font* font = TTF_OpenFont(file.c_str(), fontSize);
        return font;
    }

    static void DrawText(SDL_Renderer* renderer, TTF_Font* font, const std::string& message, SDL_Color color, int x, int y) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
        if (!surface) return;

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect dstRect = { x, y, surface->w, surface->h };

        SDL_FreeSurface(surface);
        SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
        SDL_DestroyTexture(texture);
    }

    static void DrawTextCentered(SDL_Renderer* renderer, TTF_Font* font, const std::string& message, SDL_Color color, int screenWidth, int y) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
        if (!surface) return;

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        int x = (screenWidth - surface->w) / 2;
        SDL_Rect dstRect = { x, y, surface->w, surface->h };

        SDL_FreeSurface(surface);
        SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
        SDL_DestroyTexture(texture);
    }
};

#endif // _FONT__H_
