#include <graphics/font.h>

Font* Font::LoadFont(SDL_Renderer* renderer, std::string file, int ptsize, unsigned char firstChar, 
unsigned char lastChar)
{
    //Criar nova fonte.
    Font* font = new Font;
    //Definir valores basicos.
    font->_size = ptsize;
    font->_firstChar = firstChar;
    font->_lastChar = lastChar;
    //Abrir arquivo da fonte.
    TTF_Font* ttf_font = TTF_OpenFont(file.c_str(),ptsize);
    if (ttf_font == nullptr)
        return nullptr;
    //Guardar informacoes.
    font->_lineHeight = TTF_FontHeight(ttf_font);
    //Preencher glifos.
    for(int i = font->_firstChar; i <= font->_lastChar; i++)
    {
        //Iniciar o glifo.
        struct Glyph glyph;
        //Checar se o glifo é valido.
        if (TTF_GlyphIsProvided(ttf_font,i))
        {
            //Receber as metricas do glifo atual.
            TTF_GlyphMetrics(ttf_font,i,&glyph.XMin,&glyph.XMax,&glyph.YMin,&glyph.YMax,
            &glyph.Advance);
            glyph.Width = glyph.XMax - glyph.XMin;
            glyph.Height = glyph.YMax - glyph.YMin;
            //Criar a superfice.
            SDL_Surface* tmp = TTF_RenderGlyph_Solid(ttf_font,i,{255,255,255,255});
            //Converte-la para textura.
            if (tmp != nullptr)
                glyph.Texture = SDL_CreateTextureFromSurface(renderer,tmp);
            //Limpar.
            SDL_FreeSurface(tmp);
        }
        else
        {
            glyph = {0,0,0,0,0,0,0,0};
        }
        font->_glyphs[i] = glyph;
    }
    //Limpar fonte SDL.
    TTF_CloseFont(ttf_font);
    //Retornar nova fonte.
    return font;
}

Font* Font::LoadFont(SDL_Renderer* renderer, std::string file, int ptsize)
{
    return Font::LoadFont(renderer,file,ptsize,0, sizeof(char)*256 - 1);
}

void Font::DestroyFont(Font* font)
{
    //Destruir cada textura.
    for(unsigned char i = font->_firstChar; i < font->_lastChar; i++)
    {
        struct Glyph *curr = &font->_glyphs[i];
        if (curr->Texture != nullptr)
            SDL_DestroyTexture(curr->Texture);
    }
    //Destruir estrutura principal.
    delete font;
}

void Font::Render(SDL_Renderer* renderer, Font* font, std::string text, SDL_Point position, 
SDL_Color color)
{
    Font::Render(renderer,font,text,position,color,FVec2(1),{0,0},0);
}

void Font::Render(SDL_Renderer* renderer, Font* font, std::string text, SDL_Point position, 
SDL_Color color, FVec2 scale, FontAlign align, float angle)
{
    //Calcular a origem do texto de acordo com o alinhamento.
    SDL_Point origin = {0,0};
    SDL_Point size = font->GetTextSize(text);
    //Alinhamento horizontal.
    if ((align & FA_Right) != 0)
        origin.x = size.x;
    else if ((align & FA_HCenter) != 0)
        origin.x = size.x/2;
    //Alinhamento vertical.
    if ((align & FA_Bottom) != 0)
        origin.y = size.y;
    else if ((align & FA_VCenter) != 0)
        origin.y = size.y/2;
    //Chamar metodo principal.
    Font::Render(renderer,font,text,position,color,scale,origin,0);
}

void Font::Render(SDL_Renderer* renderer, Font* font, std::string text, SDL_Point position, SDL_Color color, FVec2 scale, SDL_Point origin, float angle)
{
    //Definir inicio.
    int startX = position.x - origin.x*scale.x;
    int startY = position.y - origin.y*scale.y;
    int penX = startX;
    int penY = startY;
    //Iterar sobre cada caracter.
    for (int i = 0; i < text.length(); i++)
    {
        //Ver o caracter atual.
        unsigned char c = text[i];
        //Se o caracter for '\n', pular linha.
        if (c == '\n')
        {
            penX = startX;
            penY += font->GetLineHeight()*scale.y;
            continue;
        }
        //Receber o glifo atual.
        const Glyph *glyph = &font->GetGlyphs()[text[i]];
        //Verificar se valido.
        if (glyph->Texture == nullptr)
            continue;
        //Definir a fonte.
        SDL_Rect src;
        src.x = glyph->XMin;
        src.y = 0;
        src.w = glyph->Width;
        src.h = font->GetLineHeight();
        //Definir o destino.
        SDL_Rect dest;
        dest.x = penX+glyph->XMin;
        dest.y = penY;
        dest.w = glyph->Width * scale.x;
        dest.h = font->GetLineHeight() * scale.y;
        //Calcular origem do glifo.
        SDL_Point go = {position.x - dest.x,position.y - dest.y};
        //Definir cor.
        SDL_SetTextureColorMod(glyph->Texture,color.r,color.g,color.b);
        SDL_SetTextureAlphaMod(glyph->Texture,color.a);
        //Renderizar textura.
        SDL_RenderCopyEx(renderer,glyph->Texture,&src,&dest,angle,&go,SDL_FLIP_NONE);
        //Avancar cursor.
        penX += glyph->Advance*scale.x;
    }
}

const struct Glyph *Font::GetGlyphs() const
{
    return _glyphs;
}

int Font::GetLineHeight() const
{
    return _lineHeight;
}

SDL_Point Font::GetTextSize(std::string text) const
{
    SDL_Point total = {0,_lineHeight};
    //Iterar sobre cada elemento da string, menos o ultimo.    
    for(int i = 0; i < text.length() - 1; i++)
    {
        unsigned char current = text[i];
        //Verificar se o caracter eh o pula-linha
        if (current == '\n')
        {
            total.y += _lineHeight;
            continue;
        }
        //Adicionar o avanco do caracter.
        total.x += _glyphs[current].Advance;
    }
    //Adicionar o tamanho do ultimo caracter.
    total.x += _glyphs[text[text.length() - 1]].Width;
    //Retornar total.
    return total;
}