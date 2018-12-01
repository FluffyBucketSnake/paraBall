#include <vector>
#include <SDL2/SDL.h>

struct Margin
{
    int Top;
    int Left;
    int Bottom;
    int Right;
};

class Control
{
    public:
        virtual const SDL_Point &GetPosition() const = 0;
        virtual void SetPosition(const SDL_Point &value) = 0;
        virtual const SDL_Point &GetSize() const = 0;
        virtual void SetSize(const SDL_Point &value) = 0;
        virtual const Margin &GetPadding() const = 0;
        virtual void SetPadding(const Margin &value) = 0;
        virtual bool GetFocus() const = 0;
        virtual void SetFocus(bool value) = 0;

        virtual void Click(void *sender) = 0;
        virtual void Render(int delta, SDL_Renderer *renderer) = 0;
};

class Container
{
    public:
        virtual std::vector<Control*> &Controls() = 0;
        virtual void UpdateLayout() = 0;
        virtual void Update(int delta) = 0;
        virtual void Render(int delta, SDL_Renderer *renderer) = 0;
};