#pragma once
#include <fvec2.h>
#include <string>
#include <SDL2/SDL_ttf.h>

enum FontHAlign : Uint8
{
    FHA_Left,
    FHA_Center,
    FHA_Right
};

enum FontVAlign : Uint8
{
    FVA_Top,
    FVA_Center,
    FVA_Bottom
};

struct Glyph
{
    int XMin,XMax,YMin,YMax,Advance, Width, Height;
    SDL_Texture* Texture;
};

class Font
{
    private:
        int _size;
        struct Glyph _glyphs[256];
        unsigned char _firstChar;
        unsigned char _lastChar;
        int _lineHeight;
    public:
        const struct Glyph *GetGlyph(char c);
        int GetLineHeight();
        SDL_Point GetTextSize(std::string text);
        void Render(SDL_Renderer* renderer, std::string text, SDL_Point position, SDL_Color color);
        void Render(SDL_Renderer* renderer, std::string text, SDL_Point position, SDL_Color color, FVec2 scale, SDL_Point origin, float angle);

        static Font* LoadFont(SDL_Renderer* renderer, std::string file, int ptsize, unsigned char firstChar, unsigned char lastChar);
        static Font* LoadFont(SDL_Renderer* renderer, std::string file, int ptsize);
        static void DestroyFont(Font* font);
};