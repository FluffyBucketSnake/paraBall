#pragma once
#include <fvec2.h>
#include <string>
#include <SDL2/SDL_ttf.h>

enum FontAlign : uint8_t
{
    FA_Left = 0,
    FA_HCenter = 1,
    FA_Right = 2,

    FA_Up = 0,
    FA_VCenter = 4,
    FA_Bottom = 8,
    
    FA_Center = 5,
    FA_CenterLeft = 4,
    FA_CenterRight = 6,
    FA_CenterTop = 1,
    FA_CenterBottom = 9,

    FA_TopLeft = 0,
    FA_TopRight = 2,
    FA_BottomLeft = 8,
    FA_BottomRight = 10
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
        struct Glyph _glyphs[sizeof(char)*256];
        unsigned char _firstChar;
        unsigned char _lastChar;
        int _lineHeight;
    public:
        const struct Glyph *GetGlyphs() const;
        unsigned char GetFirstChar() const;
        unsigned char GetLastChar() const;
        int GetLineHeight() const;
        SDL_Point GetTextSize(std::string text) const;

        static void Render(SDL_Renderer* renderer, Font* font, std::string text, SDL_Point position, 
        SDL_Color color);

        static void Render(SDL_Renderer* renderer, Font* font, std::string text, SDL_Point position, 
        SDL_Color color, FVec2 scale, FontAlign align, float angle);

        static void Render(SDL_Renderer* renderer, Font* font, std::string text, SDL_Point position, 
        SDL_Color color, FVec2 scale, SDL_Point origin, float angle);

        static Font* LoadFont(SDL_Renderer* renderer, std::string file, int ptsize, 
        unsigned char firstChar, unsigned char lastChar);
        static Font* LoadFont(SDL_Renderer* renderer, std::string file, int ptsize);

        static void DestroyFont(Font* font);
};